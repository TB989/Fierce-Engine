#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce {

	class VK_Device;
	class VK_Swapchain;

	class VK_Framebuffers {
	public:
		VK_Framebuffers(VK_Device* device, VkRenderPass renderpass,VK_Swapchain* swapchain);
		~VK_Framebuffers();

		void create();
		VkFramebuffer getFramebuffer(int index) { return m_framebuffers[index]; }

	private:
		//Create info
		VkFramebufferCreateInfo m_createInfo={};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkRenderPass m_renderpass=VK_NULL_HANDLE;
		VK_Swapchain* m_swapchain=nullptr;
		std::vector<VkFramebuffer> m_framebuffers;
	};

}//end namespace