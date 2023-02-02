#include "Renderer.h"

#include "RendererBase.h"

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

RENDERER_API int renderer_loadMesh(MeshSettings settings, float* vertices, unsigned int* indices) {
    LOGGER->info("Loading mesh.");
    return 1;
}