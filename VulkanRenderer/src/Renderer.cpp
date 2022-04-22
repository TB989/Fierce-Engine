#include "Renderer.h"

#include "DLLExport.h"

#include "Common.h"

#include "VK_Context.h"

VK_Context* context;

RENDERER_API bool initRenderer(HWND dummyWindowHandle, HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new VK_Context(windowHandle);

    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleaning up renderer.");

    delete context;

    return true;
}