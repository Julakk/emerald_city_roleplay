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

typedef HRESULT(APIENTRY *EndScene_t)(LPDIRECT3DDEVICE9);
static EndScene_t oEndScene = nullptr;

// Splash logo — muncul beberapa detik pas plugin baru di-load, lalu fade out.
static IDirect3DTexture9 *g_pLogoTexture = nullptr;
static DWORD g_splashStartTick = 0;
static const DWORD SPLASH_DURATION_MS = 3000; // 3 detik tampil + fade

// Path logo dicari relatif ke folder GTA:SA (taruh logo.png di root folder
// GTA:SA, sejajar dengan gta_sa.exe / samp.exe).
static const char *LOGO_PATH = "logo.png";

static void *g_pOriginalEndSceneAddr = nullptr;
static void PatchVTable(void **vtable, int index, void *newFunc, void **outOriginal);

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    // Panggil logic gambar HUD kita dulu, baru lanjut ke EndScene asli.
    OnRenderHUD(pDevice);
    return oEndScene(pDevice);
}

// NOTE PENTING soal load PNG jadi texture:
// Cara "klasik" pakai D3DXCreateTextureFromFile() dari D3DX9 — tapi
// D3DX9 itu library LAMA yang udah gak ada di Windows SDK modern
// (deprecated dari Microsoft), jadi kalau di-compile pake toolchain
// baru (MSVC terbaru / MinGW), library ini kemungkinan gak ketemu.
// Dua opsi:
//   1. Install "DirectX SDK (June 2010)" lama buat dapetin d3dx9.h/.lib
//      (ribet, banyak project SA-MP lama masih pake ini).
//   2. Pakai library modern kayak stb_image.h (single header, gratis,
//      tinggal #include) buat decode PNG jadi raw pixel, terus bikin
//      texture manual pakai IDirect3DDevice9::CreateTexture() +
//      LockRect()/UnlockRect() buat isi pixel-nya. Ini opsi yang lebih
//      direkomendasikan sekarang.
// Skeleton ini sengaja belum implement salah satunya — isi
// LoadLogoTexture() sesuai opsi yang lu pilih.
static bool LoadLogoTexture(IDirect3DDevice9 *device)
{
    // TODO: decode LOGO_PATH -> g_pLogoTexture
    return false;
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
    // Kembalikan vtable ke fungsi asli sebelum unload plugin.
    OutputDebugStringA("[ECRP] D3D9 hook removed\n");
}

void OnRenderHUD(IDirect3DDevice9 *device)
{
    // Splash logo: muncul SPLASH_DURATION_MS pertama sejak plugin load,
    // digambar sebagai sprite di tengah/pojok layar, lalu berhenti
    // digambar (bukan literal fade, tapi cutoff — fade beneran butuh
    // alpha blend bertahap, tinggal interpolasi alpha berdasarkan waktu
    // kalau mau lebih halus).
    if (g_splashStartTick == 0) {
        g_splashStartTick = GetTickCount();
        LoadLogoTexture(device);
    }

    DWORD elapsed = GetTickCount() - g_splashStartTick;
    if (elapsed < SPLASH_DURATION_MS && g_pLogoTexture) {
        // TODO: gambar g_pLogoTexture pakai ID3DXSprite (atau manual
        // draw pakai vertex buffer quad kalau gak mau depend ke D3DX).
        // Posisi: tengah atas layar, alpha fade out di 500ms terakhir.
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
