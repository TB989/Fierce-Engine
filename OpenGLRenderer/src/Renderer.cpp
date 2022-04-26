#include "Renderer.h"

#include "DLLExport.h"

#include "openGLObjects/GL_Context.h"

#include "openGLObjects/GL_VertexAttribute.h"

GL_Context* context;

RENDERER_API bool initRenderer(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    vertexShader= new GL_Shader("Shader_Color2D.vs");
    fragmentShader = new GL_Shader("Shader_Color.fs");

    pipeline = new GL_Pipeline("Color_2D", vertexShader, fragmentShader);
    pipeline->addVertexAttribute(GL_VertexAttribute::POS2);
    pipeline->addUniformLocation("projectionMatrix");
    pipeline->addUniformLocation("modelMatrix");
    pipeline->addUniformLocation("color");
    pipeline->create();

    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleanning up renderer.");

    delete pipeline;
    delete vertexShader;
    delete fragmentShader;

    delete context;

    return true;
}