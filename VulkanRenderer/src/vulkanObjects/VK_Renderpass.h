#pragma once

#include "Common.h"
#include "VulkanObject.h"

class VK_Device;

class VK_Renderpass : public VulkanObject{
public:
	VK_Renderpass(VK_Device* device);
	~VK_Renderpass();

	void addColorAttachment(VkFormat format, bool isSwapchainAttachment);
	void addColorAttachment(VkFormat format, bool isSwapchainAttachment,VkSampleCountFlagBits sampleCount);
	void addDepthAttachment(VkFormat format);
	void addDepthAttachment(VkFormat format, VkSampleCountFlagBits sampleCount);

	void addSubpass(
		uint32_t numDepthAttachments,
		uint32_t numColorAttachments, 
		uint32_t numInputAttachments, 
		uint32_t numResolveAttachment,
		uint32_t numPreserveAttachments, uint32_t attachments[]);

	void addDependency(
		VkDependencyFlags srcSubpass, VkDependencyFlags dstSubpass,
		VkPipelineStageFlags srcStageFlags, VkPipelineStageFlags dstStageFlags,
		VkAccessFlags srcAccessMask,
		VkAccessFlags dstAccessMask);

	void create();

	VkRenderPass getRenderpass() { return renderPass; }

private:
	struct SubpassReferences{
		std::vector<VkAttachmentReference> colorAttachmentReferences;
		VkAttachmentReference depthAttachmentReference;
		std::vector<VkAttachmentReference> inputAttachmentReferences;
		VkAttachmentReference resolveReference;
	};

	VK_Device* m_device=nullptr;
	VkRenderPass renderPass=VK_NULL_HANDLE;

	uint32_t numAttachments=0;
	std::vector<VkAttachmentDescription> attachments;

	std::vector<VkSubpassDescription> subpasses;
	std::vector<SubpassReferences> subpassReferences;

	std::vector<VkSubpassDependency> dependencies;
};