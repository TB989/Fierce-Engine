#include "Renderer.h"

#include "RendererBase.h"

#include "openGLObjects/GL_Context.h"
#include "openGLObjects/GL_VBO.h"
#include "openGLObjects/GL_VAO.h"
#include "openGLObjects/GL_VertexAttribute.h" 

GL_Context* context;

GL_VAO* vao;
GL_VBO* vertexBuffer;
GL_VBO* indexBuffer;

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

    vao->unbind();
    delete vao;
    vertexBuffer->unbind();
    delete vertexBuffer;
    indexBuffer->unbind();
    delete indexBuffer;

    delete context;
    return true;
}

RENDERER_API int renderer_loadMesh(MeshSettings settings,int numVertices, float *vertices,int numIndices, unsigned int *indices) {
    LOGGER->info("Loading mesh.");

    vertexBuffer = new GL_VBO(GL_ARRAY_BUFFER);
    indexBuffer = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);

    vertexBuffer->loadData(numVertices*sizeof(float),vertices,GL_STATIC_DRAW);
    indexBuffer->loadData(numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    vao = new GL_VAO(vertexBuffer,indexBuffer);
    if (settings.is2D) {
        vao->addVertexAttribute(GL_VertexAttribute::POS2);
    }
    else {
        vao->addVertexAttribute(GL_VertexAttribute::POS3);
    }
    if (settings.hasColor) {
        vao->addVertexAttribute(GL_VertexAttribute::COLOR);
    }
    if (settings.hasTextureCoordinates) {
        vao->addVertexAttribute(GL_VertexAttribute::TEX);
    }
    if (settings.hasNormals) {
        vao->addVertexAttribute(GL_VertexAttribute::NORMAL);
    }

    return 1;
}