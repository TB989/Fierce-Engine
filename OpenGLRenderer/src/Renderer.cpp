#include "Renderer.h"

#include "DLLExport.h"

#include "GL_Context.h"

GL_Context* context;

RENDERER_API bool initRenderer(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    return true;
}