#include "Renderer.h"

#include "DLLExport.h"

#include "Common.h"

#include "VK_Context.h"
#include "VK_Device.h"
#include "VK_Renderpass.h"
#include "VK_Shader.h"
#include "VK_Pipeline.h"
#include "VK_Framebuffers.h"
#include "VK_Semaphore.h"
#include "VK_Fence.h"
#include "VK_Buffer.h"

int currentFrame = 0;

VK_Context* context;
VK_Renderpass* renderpass;
VK_Shader* vertexShader;
VK_Shader* fragmentShader;
VK_Pipeline* pipeline;
VK_Framebuffers* framebuffers;
std::vector<VK_Semaphore*> imageAvailableSemaphores;
std::vector<VK_Semaphore*> renderFinishedSemaphores;
std::vector<VK_Fence*> inFlightFences;
std::vector<VK_Fence*> imagesInFlight;
VK_Buffer* vertexBuffer;
VK_Buffer* indexBuffer;

RENDERER_API bool initRenderer(HWND dummyWindowHandle, HWND windowHandle) {
    LOGGER->info("Initializing renderer.");

    context = new VK_Context(windowHandle);
    LOGGER->info("Creating render pass.");
    renderpass = new VK_Renderpass(context->getDevice());
    LOGGER->info("Loading vertex shader.");
    vertexShader = new VK_Shader(context->getDevice(), "firstShader_vert.spv");
    LOGGER->info("Loading fragment shader.");
    fragmentShader = new VK_Shader(context->getDevice(), "firstShader_frag.spv");
    LOGGER->info("Creating pipeline.");
    pipeline = new VK_Pipeline(context->getDevice(), vertexShader,fragmentShader,renderpass);
    LOGGER->info("Creating framebuffers.");
    framebuffers = new VK_Framebuffers(context->getDevice(),context->getSwapchain(),renderpass);
    VK_Device* dev = context->getDevice();
    LOGGER->info("Creating command pool.");
    dev->createCommandPool();
    LOGGER->info("Creating command buffers.");
    dev->createCommandBuffers(3);

    imageAvailableSemaphores.resize(2);
    renderFinishedSemaphores.resize(2);
    inFlightFences.resize(2);
    imagesInFlight.resize(context->getSwapchain()->getNumImages(), VK_NULL_HANDLE);
    for (size_t i = 0; i < 2; i++) {
        imageAvailableSemaphores[i] = new VK_Semaphore(context->getDevice());
        renderFinishedSemaphores[i] = new VK_Semaphore(context->getDevice());
        inFlightFences[i] = new VK_Fence(context->getDevice());
    }

    float vertices[] = {
        -0.5f,-0.5f,1.0f,0.0f,0.0f,
        0.5f,-0.5f,0.0f,1.0f,0.0f,
        0.5f,0.5f,0.0f,0.0f,1.0f,
        -0.5f,0.5f,1.0f,1.0f,1.0f
    };

    uint16_t indices[] = {
        0, 1, 2, 2, 3, 0
    };

    LOGGER->info("Creating staging vertex buffer.");
    VK_Buffer* stagingBufferVertex=new VK_Buffer(context->getDevice(), 20 * sizeof(float), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    stagingBufferVertex->loadData(20 * sizeof(float), vertices);

    LOGGER->info("Creating vertex buffer.");
    vertexBuffer = new VK_Buffer(context->getDevice(),20*sizeof(float), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    LOGGER->info("Copy data from staging vertex buffer.");
    dev->copyBuffer(20 * sizeof(float),stagingBufferVertex->getBuffer(),vertexBuffer->getBuffer());
    delete stagingBufferVertex;

    LOGGER->info("Creating staging index buffer.");
    VK_Buffer* stagingBufferIndex = new VK_Buffer(context->getDevice(), 6 * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    stagingBufferIndex->loadData(6 * sizeof(uint16_t), indices);

    LOGGER->info("Creating index buffer.");
    indexBuffer = new VK_Buffer(context->getDevice(), 6 * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    LOGGER->info("Copy data from staging index buffer.");
    dev->copyBuffer(6 * sizeof(uint16_t), stagingBufferIndex->getBuffer(), indexBuffer->getBuffer());
    delete stagingBufferIndex;

    LOGGER->info("Recording command buffers.");
    dev->recordCommandBuffers(renderpass, framebuffers, pipeline,vertexBuffer,indexBuffer);

    return true;
}

RENDERER_API bool render() {
    VkFence fence = inFlightFences[currentFrame]->getFence();
    CHECK_VK(vkWaitForFences(context->getDevice()->getDevice(), 1, &fence, VK_TRUE, UINT64_MAX), "Failed to wait for fences.");

    uint32_t imageIndex;
    CHECK_VK(vkAcquireNextImageKHR(context->getDevice()->getDevice(),context->getSwapchain()->getId(), UINT64_MAX, imageAvailableSemaphores[currentFrame]->getSemaphore(), VK_NULL_HANDLE, &imageIndex), "Failed to aquire image.");

    if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        VkFence fence1 = imagesInFlight[imageIndex]->getFence();
        CHECK_VK(vkWaitForFences(context->getDevice()->getDevice(), 1, &fence1, VK_TRUE, UINT64_MAX), "Failed to wait for fences.");
    }
    imagesInFlight[imageIndex] = inFlightFences[currentFrame];

    VkCommandBuffer buffer = context->getDevice()->getCommandBuffer(imageIndex);

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame]->getSemaphore() };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame]->getSemaphore() };

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = nullptr;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &buffer;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    CHECK_VK(vkResetFences(context->getDevice()->getDevice(), 1, &fence), "Failed to reset fence.");

    CHECK_VK(vkQueueSubmit(context->getDevice()->getQueue(), 1, &submitInfo, inFlightFences[currentFrame]->getFence()), "Failed to submit to queue.");

    VkSwapchainKHR swapChains[] = { context->getSwapchain()->getId() };

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    CHECK_VK(vkQueuePresentKHR(context->getDevice()->getQueue(), &presentInfo), "Failed to present image.");

    currentFrame = (currentFrame + 1) % 2;

    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleaning up renderer.");

    CHECK_VK(vkDeviceWaitIdle(context->getDevice()->getDevice()), "Failed to wait for idle device.");

    delete vertexBuffer;
    delete indexBuffer;

    for (size_t i = 0; i < 2; i++) {
        delete imageAvailableSemaphores[i];
        delete renderFinishedSemaphores[i];
        delete inFlightFences[i];
    }
    delete framebuffers;
    delete pipeline;
    delete fragmentShader;
    delete vertexShader;
    delete renderpass;
    delete context;

    return true;
}