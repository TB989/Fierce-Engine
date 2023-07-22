#include "AssetManager.h"

AssetManager::AssetManager(){
    shaderManager = new ShaderManager(this);
    pipelineManager = new PipelineManager(this);
    meshManager = new MeshManager(this);
    textureManager = new TextureManager(this);
}

AssetManager::~AssetManager(){
    delete textureManager;
    delete meshManager;
    delete pipelineManager;
    delete shaderManager;
}

void AssetManager::loadShaders(){
    GL_Shader* shader;

    shader = new GL_Shader(GL_VERTEX_SHADER);
    shader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color2D.vert");
    shader->create();
    shaderManager->addShader("Shader_Color2D.vert", shader);

    shader = new GL_Shader(GL_VERTEX_SHADER);
    shader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color3D.vert");
    shader->create();
    shaderManager->addShader("Shader_Color3D.vert", shader);

    shader = new GL_Shader(GL_FRAGMENT_SHADER);
    shader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Color.frag");
    shader->create();
    shaderManager->addShader("Shader_Color.frag", shader);

    shader = new GL_Shader(GL_VERTEX_SHADER);
    shader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Texture2D.vert");
    shader->create();
    shaderManager->addShader("Shader_Texture2D.vert", shader);

    shader = new GL_Shader(GL_VERTEX_SHADER);
    shader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Texture3D.vert");
    shader->create();
    shaderManager->addShader("Shader_Texture3D.vert", shader);

    shader = new GL_Shader(GL_FRAGMENT_SHADER);
    shader->addSourceCode("C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/shaders/Shader_Texture.frag");
    shader->create();
    shaderManager->addShader("Shader_Texture.frag", shader);

    LOGGER->info("Done loading shaders.");
}

void AssetManager::loadPipelines(){
    GL_Shader* vertexShaderColor2D = shaderManager->getShader("Shader_Color2D.vert");
    GL_Shader* vertexShaderColor3D = shaderManager->getShader("Shader_Color3D.vert");
    GL_Shader* fragmentShaderColor = shaderManager->getShader("Shader_Color.frag");

    if (vertexShaderColor2D == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (vertexShaderColor3D == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (fragmentShaderColor == nullptr) {
        LOGGER->error("Failed to find fragment shader.");
        return;
    }

    GL_Pipeline* simpleColorPipeline2D = new GL_Pipeline(vertexShaderColor2D, fragmentShaderColor);
    simpleColorPipeline2D->addUniformLocation("modelMatrix");
    simpleColorPipeline2D->addUniformLocation("projectionMatrix");
    simpleColorPipeline2D->addUniformLocation("color");
    simpleColorPipeline2D->create();
    pipelineManager->addPipeline("SimpleColor2D", simpleColorPipeline2D);

    GL_Pipeline* simpleColorPipeline3D = new GL_Pipeline(vertexShaderColor3D, fragmentShaderColor);
    simpleColorPipeline3D->addUniformLocation("modelMatrix");
    simpleColorPipeline3D->addUniformLocation("viewMatrix");
    simpleColorPipeline3D->addUniformLocation("projectionMatrix");
    simpleColorPipeline3D->addUniformLocation("color");
    simpleColorPipeline3D->create();
    pipelineManager->addPipeline("SimpleColor3D", simpleColorPipeline3D);

    GL_Shader* vertexShaderTexture2D = shaderManager->getShader("Shader_Texture2D.vert");
    GL_Shader* vertexShaderTexture3D = shaderManager->getShader("Shader_Texture3D.vert");
    GL_Shader* fragmentShaderTexture = shaderManager->getShader("Shader_Texture.frag");

    if (vertexShaderTexture2D == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (vertexShaderTexture3D == nullptr) {
        LOGGER->error("Failed to find vertex shader.");
        return;
    }
    if (fragmentShaderTexture == nullptr) {
        LOGGER->error("Failed to find fragment shader.");
        return;
    }

    GL_Pipeline* simpleTexturePipeline2D = new GL_Pipeline(vertexShaderTexture2D, fragmentShaderTexture);
    simpleTexturePipeline2D->addUniformLocation("modelMatrix");
    simpleTexturePipeline2D->addUniformLocation("projectionMatrix");
    simpleTexturePipeline2D->create();
    pipelineManager->addPipeline("SimpleTexture2D", simpleTexturePipeline2D);

    GL_Pipeline* simpleTexturePipeline3D = new GL_Pipeline(vertexShaderColor3D, fragmentShaderColor);
    simpleTexturePipeline3D->addUniformLocation("modelMatrix");
    simpleTexturePipeline3D->addUniformLocation("viewMatrix");
    simpleTexturePipeline3D->addUniformLocation("projectionMatrix");
    simpleTexturePipeline3D->create();
    pipelineManager->addPipeline("SimpleTexture3D", simpleTexturePipeline3D);

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

int AssetManager::loadTexture(int width, int height, unsigned char* data){
    LOGGER->info("Loading texture.");

    GL_Texture* texture=new GL_Texture(GL_TEXTURE_2D);
    texture->loadData(width,height,data);
    return textureManager->addTexture(texture);
}
