// src/hook.h
#pragma once
#include <d3d9.h>

// Pasang hook ke vtable IDirect3DDevice9 (EndScene) supaya kita bisa
// nyisipin kode gambar HUD sebelum frame di-present ke layar.
bool InstallD3D9Hook();
void RemoveD3D9Hook();

// Callback yang isinya kode gambar HUD custom kita.
// Dipanggil otomatis tiap kali EndScene() asli SA-MP jalan.
void OnRenderHUD(IDirect3DDevice9 *device);
