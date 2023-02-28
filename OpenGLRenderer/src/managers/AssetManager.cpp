#include "AssetManager.h"

AssetManager::AssetManager(){
    shaderManager = new ShaderManager(this);
    pipelineManager = new PipelineManager(this);
    meshManager = new MeshManager(this);
}

AssetManager::~AssetManager(){
    delete meshManager;
    delete pipelineManager;
    delete shaderManager;
}

void AssetManager::loadShaders(){
    GL_Shader* vertexShader = new GL_Shader(GL_VERTEX_SHADER);
    vertexShader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color2D.vert");
    vertexShader->create();
    shaderManager->addShader("Shader_Color2D.vert", vertexShader);

    GL_Shader* vertexShader3D = new GL_Shader(GL_VERTEX_SHADER);
    vertexShader3D->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color3D.vert");
    vertexShader3D->create();
    shaderManager->addShader("Shader_Color3D.vert", vertexShader3D);

    GL_Shader* fragmentShader = new GL_Shader(GL_FRAGMENT_SHADER);
    fragmentShader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color.frag");
    fragmentShader->create();
    shaderManager->addShader("Shader_Color.frag", fragmentShader);

    LOGGER->info("Done loading shaders.");
}

void AssetManager::loadPipelines(){
    GL_Shader* vertexShader = shaderManager->getShader("Shader_Color2D.vert");
    GL_Shader* vertexShader3D = shaderManager->getShader("Shader_Color3D.vert");
    GL_Shader* fragmentShader = shaderManager->getShader("Shader_Color.frag");

    if (vertexShader == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (vertexShader3D == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (fragmentShader == nullptr) {
        LOGGER->error("Failed to find fragment shader.");
        return;
    }

    GL_Pipeline* simpleColorPipeline = new GL_Pipeline(vertexShader, fragmentShader);
    simpleColorPipeline->addUniformLocation("modelMatrix");
    simpleColorPipeline->addUniformLocation("projectionMatrix");
    simpleColorPipeline->addUniformLocation("color");
    simpleColorPipeline->create();
    pipelineManager->addPipeline("SimpleColor", simpleColorPipeline);

    GL_Pipeline* simpleColorPipeline3D = new GL_Pipeline(vertexShader3D, fragmentShader);
    simpleColorPipeline3D->addUniformLocation("modelMatrix");
    simpleColorPipeline3D->addUniformLocation("viewMatrix");
    simpleColorPipeline3D->addUniformLocation("projectionMatrix");
    simpleColorPipeline3D->addUniformLocation("color");
    simpleColorPipeline3D->create();
    pipelineManager->addPipeline("SimpleColor3D", simpleColorPipeline3D);

    LOGGER->info("Done loading pipelines.");
}

void AssetManager::loadRenderers(){
    LOGGER->info("Done loading renderers.");
}

int AssetManager::loadMesh(MeshSettings settings, int numVertices, float* vertices, int numIndices, unsigned int* indices){
    LOGGER->info("Loading mesh.");

    Mesh* mesh = new Mesh(settings, numVertices, vertices, numIndices, indices);
    return meshManager->addMesh(mesh);
}