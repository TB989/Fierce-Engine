#include "Renderer.h"

#include "RendererBase.h"

#include "openGLObjects/GL_Context.h"
#include "openGLObjects/GL_VBO.h"
#include "openGLObjects/GL_VAO.h"
#include "openGLObjects/GL_VertexAttribute.h"

GL_Context* context;

ShaderManager* shaderManager;
PipelineManager* pipelineManager;

GL_VAO* vao;
GL_VBO* vertexBuffer;
GL_VBO* indexBuffer;

RENDERER_API bool initRenderer(HWND dummyWindowHandle,HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new GL_Context(dummyWindowHandle,windowHandle);

    shaderManager = new ShaderManager();
    loadShaders(shaderManager);

    pipelineManager = new PipelineManager();
    loadPipelines(pipelineManager);

    return true;
}

RENDERER_API bool render() {
    //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    GL_Pipeline* pipeline = pipelineManager->getPipeline("SimpleColor");
    if (pipeline == nullptr) {
        LOGGER->error("Failed to find pipeline.");
    }
    else {
        pipeline->bind();
        pipeline->loadUniform("color", 0.0f, 0.0f, 1.0f);
        vao->bind();
        vao->draw();
        vao->unbind();
        pipeline->unbind();
    }

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

    delete pipelineManager;
    delete shaderManager;

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
    simpleColorPipeline->addUniformLocation("color");
    simpleColorPipeline->create();
    pipelineManager->addPipeline("SimpleColor", simpleColorPipeline);

    LOGGER->info("Done loading pipelines.");
}