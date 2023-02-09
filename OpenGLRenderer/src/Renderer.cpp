#include "Renderer.h"

#include "RendererBase.h"

#include "MathLibrary.h"

#include "openGLObjects/GL_Context.h"

GL_Context* context;

Mat4* orthographicProjectionMatrix;
Mat4* perspectiveProjectionMatrix;

ShaderManager* shaderManager;
PipelineManager* pipelineManager;
MeshManager* meshManager;

RENDERER_API bool initRenderer(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    shaderManager = new ShaderManager();
    loadShaders(shaderManager);

    pipelineManager = new PipelineManager();
    loadPipelines(pipelineManager);

    meshManager = new MeshManager();

    return true;
}

RENDERER_API bool render() {
    //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    GL_Pipeline* pipeline = pipelineManager->getPipeline("SimpleColor");
    Mesh* mesh = meshManager->getMesh(1);
    if (pipeline == nullptr||mesh==nullptr) {
        LOGGER->error("Failed to find pipeline or mesh.");
    }
    else {
        pipeline->bind();
        pipeline->loadUniform("color", 0.0f, 0.0f, 1.0f);
        Mat4* modelMatrix = new Mat4();
        modelMatrix->scale(100,100,1);
        modelMatrix->translate(50,50,0);
        pipeline->loadUniform("modelMatrix",modelMatrix);
        pipeline->loadUniform("projectionMatrix",orthographicProjectionMatrix);
        mesh->render();
        pipeline->unbind();
    }

    context->swapBuffers();
    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleanning up renderer.");

    delete meshManager;
    delete pipelineManager;
    delete shaderManager;

    delete orthographicProjectionMatrix;
    delete perspectiveProjectionMatrix;

    delete context;
    return true;
}

RENDERER_API void setOrthographicProjection(float width,float height,float n,float f) {
    orthographicProjectionMatrix = new Mat4();
    orthographicProjectionMatrix->setToOrthographicProjection(width,height,n,f);
}

RENDERER_API void setPerspectiveProjection(float aspect, float fov, float n, float f) {
    perspectiveProjectionMatrix = new Mat4();
    perspectiveProjectionMatrix->setToPerspectiveProjection(aspect, fov, n, f);
}

RENDERER_API int renderer_loadMesh(MeshSettings settings,int numVertices, float *vertices,int numIndices, unsigned int *indices) {
    LOGGER->info("Loading mesh.");

    Mesh* mesh = new Mesh(settings,numVertices,vertices,numIndices,indices);
    return meshManager->addMesh(mesh);
}

void loadShaders(ShaderManager* shaderManager){
    GL_Shader* vertexShader = new GL_Shader(GL_VERTEX_SHADER);
    vertexShader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color2D.vert");
    vertexShader->create();
    shaderManager->addShader("Shader_Color2D.vert", vertexShader);

    GL_Shader* fragmentShader = new GL_Shader(GL_FRAGMENT_SHADER);
    fragmentShader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color.frag");
    fragmentShader->create();
    shaderManager->addShader("Shader_Color.frag",fragmentShader);

    LOGGER->info("Done loading shaders.");
}

void loadPipelines(PipelineManager* pipelineManager){
    GL_Shader* vertexShader = shaderManager->getShader("Shader_Color2D.vert");
    GL_Shader* fragmentShader = shaderManager->getShader("Shader_Color.frag");

    if (vertexShader == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (fragmentShader ==nullptr) {
        LOGGER->error("Failed to find fragment shader.");
        return;
    }

    GL_Pipeline* simpleColorPipeline = new GL_Pipeline(vertexShader,fragmentShader);
    simpleColorPipeline->addUniformLocation("modelMatrix");
    simpleColorPipeline->addUniformLocation("projectionMatrix");
    simpleColorPipeline->addUniformLocation("color");
    simpleColorPipeline->create();
    pipelineManager->addPipeline("SimpleColor", simpleColorPipeline);

    LOGGER->info("Done loading pipelines.");
}