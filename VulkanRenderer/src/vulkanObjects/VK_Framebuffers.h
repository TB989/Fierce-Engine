#pragma once

#include "Common.h"

class VK_Device;
class VK_Swapchain;
class VK_Renderpass;

class VK_Framebuffers {
public:
	VK_Framebuffers(VK_Device* device, VK_Swapchain* swapchain, VK_Renderpass* renderpass);
	~VK_Framebuffers();

	VkFramebuffer getFramebuffer(int index) { return framebuffers[index]; }

private:
	VkDevice m_device;
	std::vector<VkFramebuffer> framebuffers;
};