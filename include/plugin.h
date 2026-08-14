// include/plugin.h
//
// CATATAN PENTING:
// Ini adalah skeleton umum yang mengikuti pola client-plugin SA-MP
// yang beredar di komunitas (mirip pola SAMP.Lua / MoonLoader / dsb).
// SA-MP TIDAK punya SDK plugin client resmi dari developer (beda
// dengan server plugin yang ada plugincommon.h resmi).
// Sebelum build serius, cocokkan ulang struct & export ini dengan
// header SDK client plugin yang biasa dipakai komunitas (banyak
// beredar di repo GitHub open source project client-mod SA-MP),
// karena ABI persis (urutan struct, versi) bisa beda tiap fork.
//
#pragma once

#define PLUGIN_SUPPORTS_VERSION      0x0200
#define PLUGIN_SUPPORTS_PROCESS_TICK 0x0400

// Fungsi-fungsi minimal yang WAJIB di-export DLL supaya samp.exe
// mau load plugin ini (nama fungsi harus persis, plain C export).
extern "C" {
    __declspec(dllexport) unsigned int Supports();
    __declspec(dllexport) bool Load(void **ppData);
    __declspec(dllexport) void Unload();
    __declspec(dllexport) void ProcessTick(); // dipanggil tiap frame/tick
}
