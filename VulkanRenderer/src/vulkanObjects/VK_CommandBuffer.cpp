#include "VK_CommandBuffer.h"

#include "vulkanObjects/VK_Device.h"

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

}//end namespace