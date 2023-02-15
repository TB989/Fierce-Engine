#include "Renderer.h"

#include "RendererBase.h"

#include "MathLibrary.h"

#include "openGLObjects/GL_Context.h"

GL_Context* context;

Mat4* orthographicProjectionMatrix;
Mat4* perspectiveProjectionMatrix;

AssetManager* assetManager;

RENDERER_API void renderer_init(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    orthographicProjectionMatrix = new Mat4();
    perspectiveProjectionMatrix = new Mat4();

    assetManager = new AssetManager();
    assetManager->loadShaders();
    assetManager->loadPipelines();
    assetManager->loadRenderers();
}

RENDERER_API void renderer_startFrame() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

RENDERER_API void renderer_addEntity(RenderType renderType,float &modelMatrix,int meshId,float &color) {
    GL_Renderer* renderer=assetManager->getRenderer(renderType);
    renderer->addEntity(modelMatrix,meshId,color);
}

RENDERER_API void renderer_endFrame() {

    GL_Pipeline* pipeline = pipelineManager->getPipeline("SimpleColor");
    Mesh* mesh = meshManager->getMesh(1);
    if (pipeline == nullptr || mesh == nullptr) {
        LOGGER->error("Failed to find pipeline or mesh.");
    }
    else {
        pipeline->bind();
        pipeline->loadUniform("color", 0.0f, 0.0f, 1.0f);
        Mat4* modelMatrix = new Mat4();
        modelMatrix->scale(100, 100, 1);
        modelMatrix->translate(50, 50, 0);
        pipeline->loadUniform("modelMatrix", modelMatrix);
        pipeline->loadUniform("projectionMatrix", orthographicProjectionMatrix);
        mesh->render();
        pipeline->unbind();
    }

    context->swapBuffers();
}

RENDERER_API void renderer_cleanUp() {
    LOGGER->info("Cleaning up renderer.");

    delete assetManager;

    delete orthographicProjectionMatrix;
    delete perspectiveProjectionMatrix;

    delete context;
}

RENDERER_API void renderer_setOrthographicProjection(float width,float height,float n,float f) {
    orthographicProjectionMatrix->setToOrthographicProjection(width,height,n,f);
}

RENDERER_API void renderer_setPerspectiveProjection(float aspect, float fov, float n, float f) {
    perspectiveProjectionMatrix->setToPerspectiveProjection(aspect, fov, n, f);
}

RENDERER_API int renderer_loadMesh(MeshSettings settings,int numVertices, float *vertices,int numIndices, unsigned int *indices) {
    return assetManager->loadMesh(settings,numVertices,vertices,numIndices,indices);
}