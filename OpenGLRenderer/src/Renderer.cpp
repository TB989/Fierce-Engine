#include "Renderer.h"

#include "Renderer_API.h"

#include "openGLObjects/GL_Context.h"

#include "openGLObjects/GL_VertexAttribute.h"

#include "Matrix.h"
#include "Transform.h"

GL_Context* context;

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
    delete context;
    return true;
}

RENDERER_API ShaderID addShader(ShaderType shaderType, int sourceCodeSize, char* sourceCode) {
    return 0;
}

RENDERER_API PipelineID addPipeline(ShaderID vertexShader,ShaderID fragmentShader) {
    return 0;
}

RENDERER_API void createPipeline(PipelineID id) {

}

RENDERER_API void addVertexInput(PipelineID id,VertexInput* input) {

}

RENDERER_API void addPipelineParameter(PipelineID id, ParameterType type,char* name) {
}

RENDERER_API void addPipelineRenderpass(PipelineID id, RenderpassID renderpass) {
    
}

RENDERER_API RenderpassID addRenderpass() {
    return 0;
}

RENDERER_API void createRenderpass(PipelineID id) {
    
}

RENDERER_API void addRenderpassColorAttachment(RenderpassID id) {
    
}

RENDERER_API FramebuffersID addFramebuffers() {
    return 0;
}

RENDERER_API void createFramebuffers(FramebuffersID id) {
    
}

RENDERER_API void addFramebuffersRenderpass(FramebuffersID id, RenderpassID renderpass) {
    
}