// src/hook.cpp
//
// Teknik: vtable hook pada IDirect3DDevice9::EndScene.
// Ini teknik umum yang dipakai overlay/mod tools (ImGui overlay, dsb),
// bukan sesuatu yang eksklusif buat cheat — cuma cara standar buat
// nge-inject gambar custom ke render loop game yang udah jalan.
//
#include "hook.h"
#include <windows.h>
#include <cstdio>

typedef HRESULT(APIENTRY *EndScene_t)(LPDIRECT3DDEVICE9);
static EndScene_t oEndScene = nullptr;

static void *g_pOriginalEndSceneAddr = nullptr;
static void PatchVTable(void **vtable, int index, void *newFunc, void **outOriginal);

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    // Panggil logic gambar HUD kita dulu, baru lanjut ke EndScene asli.
    OnRenderHUD(pDevice);
    return oEndScene(pDevice);
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
    // TODO: gambar HUD custom di sini, misalnya pakai ID3DXFont buat
    // teks (nama server, duit RP, level, dll) atau sprite buat logo.
    //
    // Contoh sederhana (butuh ID3DXFont yang sudah di-init sebelumnya):
    // pFont->DrawTextA(nullptr, "Emerald City Roleplay", -1, &rect,
    //                   DT_LEFT | DT_TOP, D3DCOLOR_XRGB(255, 215, 0));
}

static void PatchVTable(void **vtable, int index, void *newFunc, void **outOriginal)
{
    DWORD oldProtect;
    VirtualProtect(&vtable[index], sizeof(void *), PAGE_EXECUTE_READWRITE, &oldProtect);
    *outOriginal = vtable[index];
    vtable[index] = newFunc;
    VirtualProtect(&vtable[index], sizeof(void *), oldProtect, &oldProtect);
}
