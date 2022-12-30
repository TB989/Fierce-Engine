#include "Renderer.h"

#include "Renderer_API.h"

#include "Common.h"

#include "vulkanObjects/VK_Context.h"
#include "vulkanObjects/VK_Renderpass.h"

VK_Context* context;
VK_Renderpass* renderpass;

RENDERER_API bool initRenderer(HWND dummyWindowHandle, HWND windowHandle) {
    uint32_t subpass[10];

    LOGGER->info("Initializing renderer.");
    context = new VK_Context(windowHandle);
    renderpass = new VK_Renderpass(context->getDevice());
    renderpass->addColorAttachment(context->getDevice()->getSurfaceData()->swapchainFormat.format,true);
    subpass[0] = 0;
    renderpass->addSubpass(0,1,0,0,0,subpass);
    renderpass->create();
    return true;
}

void beginFrame() {}

void endFrame() {}

RENDERER_API bool render() {
    beginFrame();
    endFrame();
    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleaning up renderer.");
    CHECK_VK(vkDeviceWaitIdle(context->getDevice()->getDevice()), "Failed to wait for idle device.");
    delete renderpass;
    delete context;
    return true;
}

RENDERER_API ShaderID addShader(ShaderType shaderType, int sourceCodeSize, char* sourceCode) {
    return 0;
}

RENDERER_API PipelineID addPipeline(ShaderID vertexShader, ShaderID fragmentShader) {
    return 0;
}

RENDERER_API void createPipeline(PipelineID id) {

}

RENDERER_API void addVertexInput(PipelineID id, VertexInput* input) {
    
}

RENDERER_API void addPipelineParameter(PipelineID id, ParameterType type, char* name) {
    
}

RENDERER_API void addPipelineRenderpass(PipelineID id, RenderpassID renderpass) {
}

RENDERER_API RenderpassID addRenderpass() {
    return 0;
}

RENDERER_API void createRenderpass(RenderpassID id) {

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