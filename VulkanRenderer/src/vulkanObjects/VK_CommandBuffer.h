#pragma once

#include "Common.h"

class VK_Device;
class VK_CommandPool;

class VK_Renderpass;
class VK_Pipeline;

class VK_Buffer;
class VK_DescriptorSet;

class VK_CommandBuffer {
public:
	VK_CommandBuffer(VK_Device* device,VK_CommandPool* commandPool);
	~VK_CommandBuffer();

	VkCommandBuffer getCommandBuffer() { return commandBuffer; }

	void startRecording();
	void endRecording();
	void reset();

	void beginRenderPass(VK_Renderpass* renderpass,VkFramebuffer framebuffer);
	void endRenderPass();
	void bindPipeline(VK_Pipeline* pipeline);

	void bindVertexBuffer(VK_Buffer* vertexBuffer);
	void bindIndexBuffer(VK_Buffer* indexBuffer);

	void bindDescriptorSet(VK_Pipeline* pipeline,VK_DescriptorSet* descriptorSet);

	void recordRender(int vertexCount);
	void recordRenderIndexed(int indexCount);

	void recordCopy(int size,VK_Buffer* srcBuffer,VK_Buffer* dstBuffer);

private:
	VK_Device* m_device;
	VK_CommandPool* m_commandPool;

	VkCommandBuffer commandBuffer;
};