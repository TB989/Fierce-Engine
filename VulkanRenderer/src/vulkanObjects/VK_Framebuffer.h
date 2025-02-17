#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce {

	class VK_Device;
	class VK_Image;
	class VK_ImageView;

	class VK_Framebuffer {
	public:
		VK_Framebuffer(VK_Device* device, VkRenderPass renderpass);
		~VK_Framebuffer();

		void addAttachment(VkImageView imageView);
		void addDepthBuffer();
		VkFramebuffer getId() { return m_framebuffer; };

		VK_Image* getDepthBuffer() { return m_depthBuffer; }

		void create();

	private:
		//Create info
		VkFramebufferCreateInfo m_createInfo={};
		std::vector<VkImageView> m_attachments;

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkRenderPass m_renderpass=VK_NULL_HANDLE;
		VkFramebuffer m_framebuffer=VK_NULL_HANDLE;

		//Depth buffer
		VK_Image* m_depthBuffer = nullptr;
		VK_ImageView* m_depthBufferView = nullptr;
	};

}//end namespace