// src/main.cpp
#include "../include/plugin.h"
#include "../include/config.h"
#include "hook.h"
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            OutputDebugStringA("[ECRP] Plugin DLL attached\n");
            break;
        case DLL_PROCESS_DETACH:
            OutputDebugStringA("[ECRP] Plugin DLL detached\n");
            break;
    }
    return TRUE;
}

extern "C" {

__declspec(dllexport) unsigned int Supports()
{
    return PLUGIN_SUPPORTS_VERSION | PLUGIN_SUPPORTS_PROCESS_TICK;
}

__declspec(dllexport) bool Load(void **ppData)
{
    OutputDebugStringA("[ECRP] " ECRP_SERVER_NAME " client plugin loaded\n");
    InstallD3D9Hook();
    return true;
}

__declspec(dllexport) void Unload()
{
    RemoveD3D9Hook();
    OutputDebugStringA("[ECRP] Plugin unloaded\n");
}

__declspec(dllexport) void ProcessTick()
{
    // Dipanggil tiap tick/frame oleh samp.exe — tempat buat logic
    // yang perlu jalan terus-menerus (misal update data HUD).
}

} // extern "C"
