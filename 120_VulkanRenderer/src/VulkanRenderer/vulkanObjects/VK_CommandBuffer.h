#pragma once

#include "vulkan/vulkan.h"

#include <array>

namespace Fierce {

	class VK_Device;
	class VK_Pipeline;

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
		void beginRenderpass(VkRenderPass renderpass, VkFramebuffer framebuffer, bool hasDepthBuffer);
		void endRenderpass();

		void bindPipeline(VkPipeline pipeline);
		void bindVertexBuffer(VkBuffer buffer);
		void bindIndexBuffer(VkBuffer buffer);
		void bindDescriptorSet(VK_Pipeline* pipeline, VkDescriptorSet descriptorSet,int index);
		void pushConstants(VK_Pipeline* pipeline, VkShaderStageFlagBits shaderStages, uint32_t size, uint32_t offset,float* data);
		void pushConstants(VK_Pipeline* pipeline, VkShaderStageFlagBits shaderStages, uint32_t size, uint32_t offset, uint32_t* data);

		void setViewport(float width, float height);
		void setScissor(uint32_t width, uint32_t height);

		void render(int vertexCount);
		void renderIndexed(int indexCount);

		void copy(VkBuffer source, VkBuffer destination, VkDeviceSize size);
		void copy(VkBuffer source, VkImage destination, uint32_t width, uint32_t height);

		void imageBarrier(VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout);

	private:
		//Create info
		VkCommandBufferAllocateInfo m_allocateInfo={};

		//Command infos
		VkCommandBufferBeginInfo m_beginInfo={};
		VkRenderPassBeginInfo m_renderPassInfo={};

		//Copying
		VkBufferCopy m_bufferCopy = {};
		VkBufferImageCopy m_bufferImageCopy = {};
		VkImageMemoryBarrier m_imageMemoryBarrier={};

		//Misc
		VkClearValue m_clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		std::array<VkClearValue, 2> clearValues{};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkCommandPool m_commandPool=VK_NULL_HANDLE;
		VkCommandBuffer m_commandBuffer=VK_NULL_HANDLE;
	};

}//end namespace