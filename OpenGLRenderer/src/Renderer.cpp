#include "Renderer.h"

#include "RendererBase.h"
#include "MathLibrary.h"
#include "GeometryLibrary.h"

#include "openGLObjects/GL_Context.h"

GL_Context* context;

Mat4* orthographicProjectionMatrix;
Mat4* perspectiveProjectionMatrix;
Mat4* m_viewMatrix;

AssetManager* assetManager;

RENDERER_API void renderer_init(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

RENDERER_API void renderer_addEntityColor(RenderType renderType,float* modelMatrix,int meshId,float* color) {
    GL_Pipeline* pipeline = nullptr;
    Mesh* mesh = nullptr;
    Mat4* m_modelMatrix = nullptr;
    switch (renderType) {
    case SIMPLE_COLOR_2D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleColor2D");
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
        pipeline->loadUniform("projectionMatrix", perspectiveProjectionMatrix);
        mesh->render();
        pipeline->unbind();
        break;
    default:
        break;
    }
}

RENDERER_API void renderer_addEntityGeometry(RenderType renderType, GeometrySettings geometry, float* modelMatrix, int meshId, int numColors, float* colors) {
    GL_Pipeline* pipeline = nullptr;
    Mesh* mesh = nullptr;
    Mat4* m_modelMatrix = nullptr;
    int activeColor = 0;
    int count=0;
    int counter = 0;
    switch (renderType) {
    case GEOMETRY_2D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleColor2D");
        if (pipeline == nullptr) {
            LOGGER->error("Failed to find pipeline.");
        }
        mesh = assetManager->getMeshManager()->getMesh(meshId);
        if (mesh == nullptr) {
            LOGGER->error("Failed to find mesh.");
        }
        pipeline->bind();
        m_modelMatrix = new Mat4(modelMatrix);
        pipeline->loadUniform("modelMatrix", m_modelMatrix);
        pipeline->loadUniform("projectionMatrix", orthographicProjectionMatrix);

        switch (geometry.type){
        case RECTANGLE:
        case CIRCLE:
        case CIRCLE_RING:
        case TRIANGLE:
            pipeline->loadUniform("color", colors[0], colors[1], colors[2]);
            mesh->render();
            break;
        default:
            break;
        }

        pipeline->unbind();
        break;
    case GEOMETRY_3D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleColor3D");
        if (pipeline == nullptr) {
            LOGGER->error("Failed to find pipeline.");
        }
        mesh = assetManager->getMeshManager()->getMesh(meshId);
        if (mesh == nullptr) {
            LOGGER->error("Failed to find mesh.");
        }
        pipeline->bind();
        m_modelMatrix = new Mat4(modelMatrix);
        pipeline->loadUniform("modelMatrix", m_modelMatrix);
        pipeline->loadUniform("viewMatrix", m_viewMatrix);
        pipeline->loadUniform("projectionMatrix", perspectiveProjectionMatrix);

        switch (geometry.type) {
        case PLANE:
            pipeline->loadUniform("color", colors[0], colors[1], colors[2]);
            mesh->render();
            break;
        case CUBE:
            for (int i = 0; i < 6; i++) {
                pipeline->loadUniform("color", colors[activeColor*3], colors[activeColor*3+1], colors[activeColor*3+2]);
                mesh->render(i * 6, 6);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;
            }
            break;
        case CYLINDER:
            if (geometry.angle == 360.0f) {
                count = geometry.numPoints;
            }
            else {
                count = geometry.numPoints - 1;
            }

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(0, 3 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(3 * count, 3 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(6 * count, 6 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            if (geometry.angle != 360.0f) {
                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(12 * count, 6);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;

                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(12 * count + 6, 6);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;
            }
            break;
        case HOLLOW_CYLINDER:
            if (geometry.angle == 360.0f) {
                count = geometry.numPoints;
            }
            else {
                count = geometry.numPoints - 1;
            }

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(0, 6 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;
            
            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(6 * count, 6 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(12 * count, 6 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(18 * count, 6 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            if (geometry.angle != 360.0f) {
                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(24 * count, 6);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;

                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(24 * count + 6, 6);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;
            }
            break;
        case CONE:
            if (geometry.angle == 360.0f) {
                count = geometry.numPoints;
            }
            else {
                count = geometry.numPoints - 1;
            }

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(0, 3 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(3 * count, 3 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;

            if (geometry.angle != 360.0f) {
                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(6 * count, 3);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;

                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(6 * count + 3, 3);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;
            }
            break;
        case SPHERE:
            if (geometry.angle == 360.0f) {
                count = geometry.numPoints;
            }
            else {
                count = geometry.numPoints - 1;
            }

            //Circle
            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(counter, 3 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;
            counter += 3 * count;

            //Circle rings
            for (int i = 0; i < geometry.numRings - 1; i++) {
                pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
                mesh->render(counter, 6 * count);
                activeColor++;
                if (activeColor >= numColors)activeColor = 0;
                counter += 6 * count;
            }

            //Circle
            pipeline->loadUniform("color", colors[activeColor * 3], colors[activeColor * 3 + 1], colors[activeColor * 3 + 2]);
            mesh->render(counter, 3 * count);
            activeColor++;
            if (activeColor >= numColors)activeColor = 0;
            break;
        default:
            break;
        }

        pipeline->unbind();
        break;
    default:
        break;
    }
}

RENDERER_API void renderer_addEntityTexture(RenderType renderType, float* modelMatrix, int meshId, int textureId) {
    GL_Pipeline* pipeline = nullptr;
    Mesh* mesh = nullptr;
    GL_Texture* texture = nullptr;
    Mat4* m_modelMatrix = nullptr;
    switch (renderType) {
    case SIMPLE_TEXTURE_2D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleTexture2D");
        if (pipeline == nullptr) {
            LOGGER->error("Failed to find pipeline.");
        }
        mesh = assetManager->getMeshManager()->getMesh(meshId);
        if (mesh == nullptr) {
            LOGGER->error("Failed to find mesh.");
        }
        texture = assetManager->getTextureManager()->getTexture(textureId);
        if (texture == nullptr) {
            LOGGER->error("Failed to find texture.");
        }
        pipeline->bind();
        texture->bind();
        m_modelMatrix = new Mat4(modelMatrix);
        pipeline->loadUniform("modelMatrix", m_modelMatrix);
        pipeline->loadUniform("projectionMatrix", orthographicProjectionMatrix);
        mesh->render();
        texture->unbind();
        pipeline->unbind();
        break;
    case SIMPLE_TEXTURE_3D:
        pipeline = assetManager->getPipelineManager()->getPipeline("SimpleColor3D");
        if (pipeline == nullptr) {
            LOGGER->error("Failed to find pipeline.");
        }
        mesh = assetManager->getMeshManager()->getMesh(meshId);
        if (mesh == nullptr) {
            LOGGER->error("Failed to find mesh.");
        }
        texture = assetManager->getTextureManager()->getTexture(textureId);
        if (texture == nullptr) {
            LOGGER->error("Failed to find texture.");
        }
        pipeline->bind();
        texture->bind();
        m_modelMatrix = new Mat4(modelMatrix);
        pipeline->loadUniform("modelMatrix", m_modelMatrix);
        pipeline->loadUniform("viewMatrix", m_viewMatrix);
        pipeline->loadUniform("projectionMatrix", perspectiveProjectionMatrix);
        mesh->render();
        texture->unbind();
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

RENDERER_API int renderer_loadTexture(int width,int height, unsigned char* data) {
    return assetManager->loadTexture(width, height, data);
}