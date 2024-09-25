#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_CommandBuffer {
	public:
		VK_CommandBuffer(VK_Device* device,VkCommandPool commandPool);
		~VK_CommandBuffer();

		void create();
		VkCommandBuffer getId() { return m_commandBuffer; }

		void reset();

	public:
		void updateRenderArea();

		void startRecording();
		void endRecording();
		void beginRenderpass(VkRenderPass renderpass, VkFramebuffer framebuffer);
		void endRenderpass();

		void bindPipeline(VkPipeline pipeline);
		void bindVertexBuffer(VkBuffer buffer);
		void bindIndexBuffer(VkBuffer buffer);
		void setViewport(float width, float height);
		void setScissor(uint32_t width, uint32_t height);
		void render(int vertexCount);
		void renderIndexed(int indexCount);

		void copy(VkBuffer source, VkBuffer destination, VkDeviceSize size);

	private:
		//Create info
		VkCommandBufferAllocateInfo m_allocateInfo={};

		//Command infos
		VkCommandBufferBeginInfo m_beginInfo={};
		VkRenderPassBeginInfo m_renderPassInfo={};
		VkBufferCopy m_copyInfo = {};

		//Misc
		VkClearValue m_clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkCommandPool m_commandPool=VK_NULL_HANDLE;
		VkCommandBuffer m_commandBuffer=VK_NULL_HANDLE;
	};

}//end namespace