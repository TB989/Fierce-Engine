#include <windows.h>

#include <iostream>

#include "DLLExport.h"

#include "Logger.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    Logger* logger = nullptr;

    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        logger = new Logger("VK1");
        logger->warn("Hello from VulkanRenderer!");

        break;

    case DLL_THREAD_ATTACH:
        
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
       
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
       
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

RENDERER_API void testFunc() {
    Logger* logger = new Logger("VK2");
    logger->error("Test from VulkanRenderer!");
    delete logger;
}