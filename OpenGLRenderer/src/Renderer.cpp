#include "Renderer.h"

#include "RendererBase.h"

#include "openGLObjects/GL_Context.h"

GL_Context* context;

RENDERER_API bool initRenderer(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    return true;
}

RENDERER_API bool render() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    context->swapBuffers();
    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleanning up renderer.");
    delete context;
    return true;
}