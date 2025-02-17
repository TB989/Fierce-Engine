#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Renderpass {
	public:
		VK_Renderpass(VK_Device* device);
		~VK_Renderpass();

		void addDepthBuffer();

		void create();
		VkRenderPass getId() { return m_renderPass; }

		bool hasDepthBuffer() { return m_hasDepthBuffer; }

	private:
		bool m_hasDepthBuffer = false;

		//Create info
		VkRenderPassCreateInfo m_renderPassCreateInfo={};

		//Attachments
		VkAttachmentDescription m_colorAttachmentDescription={};
		VkAttachmentReference m_colorAttachmentReference={};

		VkAttachmentDescription m_depthAttachmentDescription = {};
		VkAttachmentReference m_depthAttachmentReference = {};

		//Subpasses
		VkSubpassDependency m_subpassDependency={};
		VkSubpassDescription m_subpassDescription={};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkRenderPass m_renderPass=VK_NULL_HANDLE;
	};

}//end namespace