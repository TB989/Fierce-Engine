#include "VK_CommandBuffer.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Pipeline.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

	VK_CommandBuffer::VK_CommandBuffer(VK_Device* device, VkCommandPool commandPool){
		m_device = device;
		m_commandPool = commandPool;

		m_allocateInfo={};
		m_allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		m_allocateInfo.pNext = nullptr;
		m_allocateInfo.commandPool = commandPool;
		m_allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		m_allocateInfo.commandBufferCount = 1;

		m_beginInfo={};
		m_beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		m_beginInfo.pNext = nullptr;
		m_beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		m_beginInfo.pInheritanceInfo = nullptr;

		m_renderPassInfo={};
		m_renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		m_renderPassInfo.pNext = nullptr;
		m_renderPassInfo.renderArea.offset = { 0, 0 };
		m_renderPassInfo.renderArea.extent = { m_device->getSurfaceData()->swapchainWidth,  m_device->getSurfaceData()->swapchainHeight };
		m_renderPassInfo.clearValueCount = 1;
		m_renderPassInfo.pClearValues = &m_clearColor;

		m_bufferCopy = {};
		m_bufferCopy.srcOffset = 0;
		m_bufferCopy.dstOffset = 0;

		m_bufferImageCopy = {};
		m_bufferImageCopy.bufferOffset = 0;
		m_bufferImageCopy.bufferRowLength = 0;
		m_bufferImageCopy.bufferImageHeight = 0;
		m_bufferImageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		m_bufferImageCopy.imageSubresource.mipLevel = 0;
		m_bufferImageCopy.imageSubresource.baseArrayLayer = 0;
		m_bufferImageCopy.imageSubresource.layerCount = 1;
		m_bufferImageCopy.imageOffset = { 0, 0, 0 };

		m_imageMemoryBarrier = {};
		m_imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		m_imageMemoryBarrier.pNext = nullptr;
		m_imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		m_imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		m_imageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		m_imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
		m_imageMemoryBarrier.subresourceRange.levelCount = 1;
		m_imageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
		m_imageMemoryBarrier.subresourceRange.layerCount = 1;
	}

	VK_CommandBuffer::~VK_CommandBuffer(){
		vkFreeCommandBuffers(m_device->getDevice(), m_commandPool, 1, &m_commandBuffer);
	}

	void VK_CommandBuffer::create(){
		if (vkAllocateCommandBuffers(m_device->getDevice(), &m_allocateInfo, &m_commandBuffer) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to allocate command buffer.");
		}
	}

	void VK_CommandBuffer::reset(){
		if (vkResetCommandBuffer(m_commandBuffer, 0)!=VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to reset command buffer.");
		}
	}

	void VK_CommandBuffer::updateRenderArea(){
		m_renderPassInfo.renderArea.extent = { m_device->getSurfaceData()->swapchainWidth,  m_device->getSurfaceData()->swapchainHeight };
	}

	void VK_CommandBuffer::startRecording(){
		if (vkBeginCommandBuffer(m_commandBuffer, &m_beginInfo)!=VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to start recording command buffer.");
		}
	}

	void VK_CommandBuffer::endRecording(){
		if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to end recording command buffer.");
		}
	}

	void VK_CommandBuffer::beginRenderpass(VkRenderPass renderpass,VkFramebuffer framebuffer){
		m_renderPassInfo.renderPass = renderpass;
		m_renderPassInfo.framebuffer = framebuffer;
		
		vkCmdBeginRenderPass(m_commandBuffer, &m_renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VK_CommandBuffer::endRenderpass(){
		vkCmdEndRenderPass(m_commandBuffer);
	}

	void VK_CommandBuffer::bindPipeline(VkPipeline pipeline){
		vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
	}

	void VK_CommandBuffer::bindVertexBuffer(VkBuffer buffer){
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(m_commandBuffer, 0, 1, &buffer, offsets);
	}

	void VK_CommandBuffer::bindIndexBuffer(VkBuffer buffer){
		vkCmdBindIndexBuffer(m_commandBuffer, buffer, 0, VK_INDEX_TYPE_UINT16);
	}

	void VK_CommandBuffer::bindDescriptorSet(VK_Pipeline* pipeline,VkDescriptorSet descriptorSet,int index){
		vkCmdBindDescriptorSets(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getLayout(), index,1, &descriptorSet, 0, nullptr);
	}

	void VK_CommandBuffer::setViewport(float width,float height){
		VkViewport viewport={};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = width;
		viewport.height = height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(m_commandBuffer, 0, 1, &viewport);
	}

	void VK_CommandBuffer::setScissor(uint32_t width,uint32_t height){
		VkRect2D scissor={};
		scissor.offset = { 0, 0 };
		scissor.extent.width=width;
		scissor.extent.height = height;
		vkCmdSetScissor(m_commandBuffer, 0, 1, &scissor);
	}

	void VK_CommandBuffer::render(int vertexCount){
		vkCmdDraw(m_commandBuffer, vertexCount, 1, 0, 0);
	}

	void VK_CommandBuffer::renderIndexed(int indexCount){
		vkCmdDrawIndexed(m_commandBuffer, indexCount, 1, 0, 0, 0);
	}

	void VK_CommandBuffer::copy(VkBuffer source, VkBuffer destination,VkDeviceSize size){
		m_bufferCopy.size = size;
		vkCmdCopyBuffer(m_commandBuffer, source, destination, 1, &m_bufferCopy);
	}

	void VK_CommandBuffer::copy(VkBuffer source, VkImage destination, uint32_t width,uint32_t height){
		m_bufferImageCopy.imageExtent = { width,height,1 };
		vkCmdCopyBufferToImage(m_commandBuffer,source,destination,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,1,&m_bufferImageCopy);
	}

	void VK_CommandBuffer::imageBarrier(VkImage image,VkImageLayout oldLayout,VkImageLayout newLayout){
		m_imageMemoryBarrier.image = image;
		m_imageMemoryBarrier.oldLayout = oldLayout;
		m_imageMemoryBarrier.newLayout = newLayout;

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
			m_imageMemoryBarrier.srcAccessMask = 0;
			m_imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if(oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL){
			m_imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			m_imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else {
			RenderSystem::LOGGER->error("Defined layout transition is not implemented.");
			return;
		}

		vkCmdPipelineBarrier(m_commandBuffer, sourceStage,destinationStage, 0, 0, nullptr, 0, nullptr, 1, &m_imageMemoryBarrier);
	}

}//end namespace