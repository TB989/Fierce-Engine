#include "Renderer.h"

#include "Main.h"
#include "DLLExport.h"

RENDERER_API bool initRenderer(HWND dummyWindowHandle, HWND windowHandle) {
    Main::LOGGER->info("Initializing renderer.");

    return true;
}