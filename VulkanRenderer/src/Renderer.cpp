#include "Renderer.h"

#include "DLLExport.h"

#include "Common.h"

#include "VK_Context.h"
#include "VK_Device.h"
#include "VK_Renderpass.h"
#include "VK_Shader.h"
#include "VK_Pipeline.h"
#include "VK_Framebuffers.h"
#include "VK_DescriptorPool.h"

#include "VK_Buffer.h"

#include "Matrix.h"

#include <chrono>

VK_Context* context;
VK_Renderpass* renderpass;
VK_Shader* vertexShader;
VK_Shader* fragmentShader;
VK_Pipeline* pipeline;
VK_Framebuffers* framebuffers;
VK_DescriptorPool* descriptorPool;

VK_Buffer* vertexBuffer;
VK_Buffer* indexBuffer;
Mat4 orthographicProjectionMatrix;
Mat4 modelMatrix;

const int NUM_FRAMES_IN_FLIGHT = 2;
uint32_t imageIndex;
int currentFrame = 0;
FrameData framesData[NUM_FRAMES_IN_FLIGHT];

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
    LOGGER->info("Creating descriptor pool.");
    descriptorPool = new VK_DescriptorPool(context->getDevice());

    LOGGER->info("Creating frame ressources.");
    for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
        framesData[i].imageAvailableSemaphore = new VK_Semaphore(context->getDevice());
        framesData[i].renderFinishedSemaphore = new VK_Semaphore(context->getDevice());
        framesData[i].renderFinishedFence = new VK_Fence(context->getDevice());

        framesData[i].commandPool = new VK_CommandPool(context->getDevice());
        framesData[i].commandBuffer = new VK_CommandBuffer(context->getDevice(), framesData[i].commandPool);

        framesData[i].UBO = new VK_Buffer(context->getDevice(), 2 * 16 * sizeof(float), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        framesData[i].descriptorSet = new VK_DescriptorSet(context->getDevice(),descriptorPool,pipeline);
        framesData[i].descriptorSet->update(framesData[i].UBO);
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

    LOGGER->info("Creating staging index buffer.");
    VK_Buffer* stagingBufferIndex = new VK_Buffer(context->getDevice(), 6 * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    stagingBufferIndex->loadData(6 * sizeof(uint16_t), indices);

    LOGGER->info("Creating index buffer.");
    indexBuffer = new VK_Buffer(context->getDevice(), 6 * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    LOGGER->info("Copy data to gpu.");
    framesData[0].commandBuffer->startRecording();
    framesData[0].commandBuffer->recordCopy(20 * sizeof(float),stagingBufferVertex,vertexBuffer);
    framesData[0].commandBuffer->recordCopy(6 * sizeof(uint16_t), stagingBufferIndex, indexBuffer);
    framesData[0].commandBuffer->endRecording();
    context->getDevice()->submitCommandBuffer(framesData[0].commandBuffer,nullptr,nullptr,0);
    vkQueueWaitIdle(context->getDevice()->getQueue());
    framesData[0].commandBuffer->reset();
    delete stagingBufferVertex;
    delete stagingBufferIndex;

    LOGGER->info("Creating matrices.");
    orthographicProjectionMatrix = Mat4();
    orthographicProjectionMatrix.setToOrthographicProjection(800.0f, 600.0f, -1.0f, 1.0f);
    modelMatrix = Mat4();
    modelMatrix.setToTransform(Transform2D(10.0f, 10.0f, 100.0f, 100.0f, 0.0f));

    return true;
}

void beginFrame() {
    FrameData& frameData = framesData[currentFrame];
    VkFence fence = frameData.renderFinishedFence->getFence();

    CHECK_VK(vkWaitForFences(context->getDevice()->getDevice(), 1, &fence, VK_TRUE, UINT64_MAX), "Failed to wait for fences.");
    imageIndex=context->getDevice()->getNextImageIndex(context->getSwapchain(), frameData.imageAvailableSemaphore);
    CHECK_VK(vkResetFences(context->getDevice()->getDevice(), 1, &fence), "Failed to reset fence.");
    frameData.commandBuffer->reset();
}

void endFrame() {
    FrameData& frameData = framesData[currentFrame];

    context->getDevice()->submitCommandBuffer(frameData.commandBuffer, frameData.imageAvailableSemaphore, frameData.renderFinishedSemaphore, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
    context->getDevice()->presentImage(context->getSwapchain(),imageIndex, frameData.renderFinishedSemaphore);

    currentFrame = (currentFrame + 1) % NUM_FRAMES_IN_FLIGHT;
}

RENDERER_API bool render() {
    LOGGER->info("render");

    FrameData& frameData = framesData[currentFrame];

    beginFrame();

    //Update UBOs
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    modelMatrix.rotateZ(time * 90.0f);

    float* mat1 = orthographicProjectionMatrix.get();
    float* mat2 = modelMatrix.get();

    frameData.UBO->loadData(mat1,mat2);

    //Record command buffer
    frameData.commandBuffer->startRecording();
    frameData.commandBuffer->beginRenderPass(renderpass,framebuffers->getFramebuffer(imageIndex));
    frameData.commandBuffer->bindPipeline(pipeline);
    frameData.commandBuffer->bindVertexBuffer(vertexBuffer);
    frameData.commandBuffer->bindIndexBuffer(indexBuffer);
    frameData.commandBuffer->bindDescriptorSet(pipeline,frameData.descriptorSet);
    frameData.commandBuffer->recordRenderIndexed(6);
    frameData.commandBuffer->endRenderPass();
    frameData.commandBuffer->endRecording();

    endFrame();

    return true;
}

RENDERER_API bool cleanUpRenderer() {
    LOGGER->info("Cleaning up renderer.");

    CHECK_VK(vkDeviceWaitIdle(context->getDevice()->getDevice()), "Failed to wait for idle device.");

    delete vertexBuffer;
    delete indexBuffer;

    for (int i = 0; i < NUM_FRAMES_IN_FLIGHT; i++) {
        delete framesData[i].imageAvailableSemaphore;
        delete framesData[i].renderFinishedSemaphore;
        delete framesData[i].renderFinishedFence;

        delete framesData[i].commandPool;
        delete framesData[i].commandBuffer;

        delete framesData[i].UBO;
        delete framesData[i].descriptorSet;
    }

    delete descriptorPool;
    delete framebuffers;
    delete pipeline;
    delete fragmentShader;
    delete vertexShader;
    delete renderpass;
    delete context;

    return true;
}