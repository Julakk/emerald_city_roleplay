// src/hook.cpp
//
// Teknik: vtable hook pada IDirect3DDevice9::EndScene.
// Ini teknik umum yang dipakai overlay/mod tools (ImGui overlay, dsb),
// bukan sesuatu yang eksklusif buat cheat — cuma cara standar buat
// nge-inject gambar custom ke render loop game yang udah jalan.
//
#include "hook.h"
#include "../include/config.h"
#include <windows.h>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb_image.h"

typedef HRESULT(APIENTRY *EndScene_t)(LPDIRECT3DDEVICE9);
static EndScene_t oEndScene = nullptr;

// Splash logo — muncul beberapa detik pas plugin baru di-load, lalu fade out.
static IDirect3DTexture9 *g_pLogoTexture = nullptr;
static int g_logoWidth = 0;
static int g_logoHeight = 0;
static DWORD g_splashStartTick = 0;
static const DWORD SPLASH_HOLD_MS = 2000;  // tampil penuh 2 detik
static const DWORD SPLASH_FADE_MS = 1000;  // lalu fade out 1 detik
static const DWORD SPLASH_DURATION_MS = SPLASH_HOLD_MS + SPLASH_FADE_MS;

// Path logo dicari relatif ke folder GTA:SA (taruh logo.png di root folder
// GTA:SA, sejajar dengan gta_sa.exe / samp.exe).
static const char *LOGO_PATH = "logo.png";

// Vertex format sederhana buat quad textured: posisi layar (sudah
// ter-transform) + warna (dipakai buat alpha fade) + koordinat texture.
struct HudVertex {
    float x, y, z, rhw;
    DWORD color;
    float u, v;
};
#define HUD_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

static void *g_pOriginalEndSceneAddr = nullptr;
static void PatchVTable(void **vtable, int index, void *newFunc, void **outOriginal);

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    // Panggil logic gambar HUD kita dulu, baru lanjut ke EndScene asli.
    OnRenderHUD(pDevice);
    return oEndScene(pDevice);
}

// Decode PNG pakai stb_image (single-header, gratis, gak perlu D3DX9/DirectX
// SDK lama), lalu upload manual ke IDirect3DTexture9 lewat LockRect.
static bool LoadLogoTexture(IDirect3DDevice9 *device)
{
    int channels = 0;
    unsigned char *pixels = stbi_load(LOGO_PATH, &g_logoWidth, &g_logoHeight, &channels, 4 /* force RGBA */);
    if (!pixels) {
        char buf[256];
        sprintf(buf, "[ECRP] Gagal load %s (pastikan file ada di folder GTA:SA)\n", LOGO_PATH);
        OutputDebugStringA(buf);
        return false;
    }

    HRESULT hr = device->CreateTexture(
        g_logoWidth, g_logoHeight, 1, 0,
        D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &g_pLogoTexture, nullptr);

    if (FAILED(hr)) {
        stbi_image_free(pixels);
        OutputDebugStringA("[ECRP] CreateTexture buat logo gagal\n");
        return false;
    }

    D3DLOCKED_RECT locked;
    g_pLogoTexture->LockRect(0, &locked, nullptr, 0);
    BYTE *dst = static_cast<BYTE *>(locked.pBits);

    for (int y = 0; y < g_logoHeight; y++) {
        BYTE *dstRow = dst + y * locked.Pitch;
        unsigned char *srcRow = pixels + y * g_logoWidth * 4;
        for (int x = 0; x < g_logoWidth; x++) {
            // stb_image kasih RGBA, D3DFMT_A8R8G8B8 butuh urutan BGRA di memory.
            unsigned char r = srcRow[x * 4 + 0];
            unsigned char g = srcRow[x * 4 + 1];
            unsigned char b = srcRow[x * 4 + 2];
            unsigned char a = srcRow[x * 4 + 3];
            dstRow[x * 4 + 0] = b;
            dstRow[x * 4 + 1] = g;
            dstRow[x * 4 + 2] = r;
            dstRow[x * 4 + 3] = a;
        }
    }

    g_pLogoTexture->UnlockRect(0);
    stbi_image_free(pixels);

    OutputDebugStringA("[ECRP] Logo texture berhasil di-load\n");
    return true;
}

// Gambar g_pLogoTexture sebagai quad di tengah-atas layar, dengan alpha
// yang turun bertahap di SPLASH_FADE_MS terakhir (efek fade out).
static void DrawSplashLogo(IDirect3DDevice9 *device, float alpha01)
{
    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);

    float logoW = 220.0f;
    float logoH = logoW * (static_cast<float>(g_logoHeight) / static_cast<float>(g_logoWidth));
    float cx = vp.Width / 2.0f;
    float top = 40.0f;

    BYTE alphaByte = static_cast<BYTE>(alpha01 * 255.0f);
    DWORD color = D3DCOLOR_ARGB(alphaByte, 255, 255, 255);

    HudVertex verts[4] = {
        { cx - logoW / 2, top,           0.0f, 1.0f, color, 0.0f, 0.0f },
        { cx + logoW / 2, top,           0.0f, 1.0f, color, 1.0f, 0.0f },
        { cx - logoW / 2, top + logoH,   0.0f, 1.0f, color, 0.0f, 1.0f },
        { cx + logoW / 2, top + logoH,   0.0f, 1.0f, color, 1.0f, 1.0f },
    };

    device->SetTexture(0, g_pLogoTexture);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    device->SetFVF(HUD_FVF);
    device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(HudVertex));
    device->SetTexture(0, nullptr);
}

bool InstallD3D9Hook()
{
    // NOTE: Di implementasi nyata, device D3D9 harus diambil dari game
    // yang lagi jalan (biasanya lewat CreateDevice hook atau scan memory
    // buat cari pointer device SA-MP). Bagian ini sengaja disederhanakan
    // jadi placeholder — isi detail pengambilan device sesuai SDK/header
    // yang lu pakai.
    //
    // void **vtable = GetSampD3D9DeviceVTable();
    // PatchVTable(vtable, 42 /* index EndScene */, (void*)hkEndScene, (void**)&oEndScene);

    OutputDebugStringA("[ECRP] D3D9 hook installed (placeholder)\n");
    return true;
}

void RemoveD3D9Hook()
{
    if (g_pLogoTexture) {
        g_pLogoTexture->Release();
        g_pLogoTexture = nullptr;
    }
    // Kembalikan vtable ke fungsi asli sebelum unload plugin.
    OutputDebugStringA("[ECRP] D3D9 hook removed\n");
}

void OnRenderHUD(IDirect3DDevice9 *device)
{
    if (g_splashStartTick == 0) {
        g_splashStartTick = GetTickCount();
        LoadLogoTexture(device);
    }

    DWORD elapsed = GetTickCount() - g_splashStartTick;
    if (elapsed < SPLASH_DURATION_MS && g_pLogoTexture) {
        float alpha = 1.0f;
        if (elapsed > SPLASH_HOLD_MS) {
            DWORD fadeElapsed = elapsed - SPLASH_HOLD_MS;
            alpha = 1.0f - (static_cast<float>(fadeElapsed) / static_cast<float>(SPLASH_FADE_MS));
            if (alpha < 0.0f) alpha = 0.0f;
        }
        DrawSplashLogo(device, alpha);
    }

    // TODO: HUD permanen (nama server, duit RP, level, dll) digambar
    // di sini juga, terpisah dari splash — biasanya pakai teks lewat
    // font custom (bitmap font atau library kayak ID3DXFont/stb_truetype).
}

static void PatchVTable(void **vtable, int index, void *newFunc, void **outOriginal)
{
    DWORD oldProtect;
    VirtualProtect(&vtable[index], sizeof(void *), PAGE_EXECUTE_READWRITE, &oldProtect);
    *outOriginal = vtable[index];
    vtable[index] = newFunc;
    VirtualProtect(&vtable[index], sizeof(void *), oldProtect, &oldProtect);
}
