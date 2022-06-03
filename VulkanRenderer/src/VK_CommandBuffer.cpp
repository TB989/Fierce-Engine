#include "VK_CommandBuffer.h"

#include "VK_Device.h"
#include "VK_CommandPool.h"

#include "VK_Renderpass.h"
#include "VK_Pipeline.h"

#include "VK_Buffer.h"
#include "VK_DescriptorSet.h"

VK_CommandBuffer::VK_CommandBuffer(VK_Device* device, VK_CommandPool* commandPool){
    m_device = device;
    m_commandPool = commandPool;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;
    allocInfo.commandPool = commandPool->getCommandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    CHECK_VK(vkAllocateCommandBuffers(device->getDevice(), &allocInfo, &commandBuffer), "Failed to allocate command buffers.");
}

VK_CommandBuffer::~VK_CommandBuffer(){
    vkFreeCommandBuffers(m_device->getDevice(), m_commandPool->getCommandPool(), 1, &commandBuffer);
}

void VK_CommandBuffer::startRecording(){
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.pNext = nullptr;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    beginInfo.pInheritanceInfo = nullptr;
    CHECK_VK(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording command buffer.");
}

void VK_CommandBuffer::endRecording(){
    CHECK_VK(vkEndCommandBuffer(commandBuffer), "Failed to end recording command buffer.");
}

void VK_CommandBuffer::reset(){
    CHECK_VK(vkResetCommandBuffer(commandBuffer,0),"Failed to reset command buffer.");
}

void VK_CommandBuffer::beginRenderPass(VK_Renderpass* renderpass, VkFramebuffer framebuffer){
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = nullptr;
    renderPassInfo.renderPass = renderpass->getRenderpass();
    renderPassInfo.framebuffer = framebuffer;
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = { m_device->getSurfaceData()->swapchainWidth,  m_device->getSurfaceData()->swapchainHeight };
    VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VK_CommandBuffer::endRenderPass() {
    vkCmdEndRenderPass(commandBuffer);
}

void VK_CommandBuffer::bindPipeline(VK_Pipeline* pipeline){
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipeline());
}

void VK_CommandBuffer::bindVertexBuffer(VK_Buffer* vertexBuffer){
    VkBuffer vertexBuffers[] = { vertexBuffer->getBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
}

void VK_CommandBuffer::bindIndexBuffer(VK_Buffer* indexBuffer){
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT16);
}

void VK_CommandBuffer::bindDescriptorSet(VK_Pipeline* pipeline, VK_DescriptorSet* descriptorSet){
    VkDescriptorSet desc = descriptorSet->getDescriptorSet();
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipelineLayout(), 0, 1, &desc, 0, nullptr);
}

void VK_CommandBuffer::recordRender(int vertexCount){
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

void VK_CommandBuffer::recordRenderIndexed(int indexCount) {
    vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
}

void VK_CommandBuffer::recordCopy(int size, VK_Buffer* srcBuffer, VK_Buffer* dstBuffer){
    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer->getBuffer(), dstBuffer->getBuffer(), 1, &copyRegion);
}