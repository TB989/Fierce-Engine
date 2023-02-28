#include "Renderer.h"

#include "RendererBase.h"

#include "MathLibrary.h"

#include "openGLObjects/GL_Context.h"

GL_Context* context;

Mat4* orthographicProjectionMatrix;
Mat4* perspectiveProjectionMatrix;
Mat4* m_viewMatrix;

AssetManager* assetManager;

RENDERER_API void renderer_init(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    orthographicProjectionMatrix = new Mat4();
    perspectiveProjectionMatrix = new Mat4();

    m_viewMatrix = new Mat4();

    assetManager = new AssetManager();
    assetManager->loadShaders();
    assetManager->loadPipelines();
    assetManager->loadRenderers();
}

RENDERER_API void renderer_startFrame() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

RENDERER_API void renderer_addEntity(RenderType renderType,float* modelMatrix,int meshId,float* color) {
    GL_Pipeline* pipeline = nullptr;
    Mesh* mesh = nullptr;
    Mat4* m_modelMatrix = nullptr;
    switch (renderType) {
    case SIMPLE_COLOR_2D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleColor");
        if (pipeline == nullptr) {
            LOGGER->error("Failed to find pipeline.");
        }
        mesh = assetManager->getMeshManager()->getMesh(meshId);
        if (mesh == nullptr) {
            LOGGER->error("Failed to find mesh.");
        }
        pipeline->bind();
        pipeline->loadUniform("color", color[0], color[1], color[2]);
        m_modelMatrix = new Mat4(modelMatrix);
        pipeline->loadUniform("modelMatrix", m_modelMatrix);
        pipeline->loadUniform("projectionMatrix", orthographicProjectionMatrix);
        mesh->render();
        pipeline->unbind();
        break;
    case SIMPLE_COLOR_3D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleColor3D");
        if (pipeline == nullptr) {
            LOGGER->error("Failed to find pipeline.");
        }
        mesh = assetManager->getMeshManager()->getMesh(meshId);
        if (mesh == nullptr) {
            LOGGER->error("Failed to find mesh.");
        }
        pipeline->bind();
        pipeline->loadUniform("color", color[0], color[1], color[2]);
        m_modelMatrix = new Mat4(modelMatrix);
        pipeline->loadUniform("modelMatrix", m_modelMatrix);
        pipeline->loadUniform("viewMatrix", m_viewMatrix);
        pipeline->loadUniform("projectionMatrix", orthographicProjectionMatrix);
        mesh->render();
        pipeline->unbind();
        break;
    default:
        break;
    }
}

RENDERER_API void renderer_endFrame() {
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

RENDERER_API void renderer_setViewMatrix(float* viewMatrix) {
    m_viewMatrix = new Mat4(viewMatrix);
}

RENDERER_API int renderer_loadMesh(MeshSettings settings,int numVertices, float *vertices,int numIndices, unsigned int *indices) {
    return assetManager->loadMesh(settings,numVertices,vertices,numIndices,indices);
}