#include "Renderer.h"

#include "Main.h"
#include "DLLExport.h"

#include "GL_Context.h"

GL_Context* context;

RENDERER_API bool initRenderer() {
    Main::LOGGER->info("Initializing renderer.");

    context = new GL_Context();

    return true;
}