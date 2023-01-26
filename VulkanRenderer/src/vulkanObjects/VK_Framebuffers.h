#pragma once

#include "src/Common.h"
#include "VulkanObject.h"

class VK_Device;
class VK_Swapchain;
class VK_Renderpass;

class VK_Framebuffers : public VulkanObject{
public:
	VK_Framebuffers(VK_Device* device, VK_Swapchain* swapchain);
	~VK_Framebuffers();

	void create();

	void addRenderPass(VK_Renderpass* renderpass) { m_renderpass = renderpass; }

	VkFramebuffer getFramebuffer(int index) { return framebuffers[index]; }

private:
	VK_Device* m_device;
	VK_Swapchain* m_swapchain;
	VK_Renderpass* m_renderpass;
	std::vector<VkFramebuffer> framebuffers;
};