#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Renderpass {
	public:
		VK_Renderpass(VK_Device* device);
		~VK_Renderpass();

		void create();
		VkRenderPass getId() { return m_renderPass; }

	private:
		//Create info
		VkRenderPassCreateInfo m_renderPassCreateInfo={};

		//Attachments
		VkAttachmentDescription m_colorAttachmentDescription={};
		VkAttachmentReference m_colorAttachmentReference={};

		//Subpasses
		VkSubpassDependency m_subpassDependency={};
		VkSubpassDescription m_subpassDescription={};

		//Vulkan objects
		VkDevice m_device=VK_NULL_HANDLE;
		VkRenderPass m_renderPass=VK_NULL_HANDLE;
	};

}//end namespace