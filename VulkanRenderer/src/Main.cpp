#include "Common.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpReserved){
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        LOGGER->info("Process attached to Vulkan renderer.");
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        LOGGER->info("Process dettached from Vulkan renderer.");
        break;
    }
    return TRUE;
}