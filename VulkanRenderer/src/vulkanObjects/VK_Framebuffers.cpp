#include "VK_Framebuffers.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Swapchain.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Framebuffers::VK_Framebuffers(VK_Device* device,VkRenderPass renderpass,VK_Swapchain* swapchain){
		m_device = device;
		m_renderpass = renderpass;
		m_swapchain = swapchain;
		m_framebuffers.resize(swapchain->getNumImages());

		m_createInfo={};
		m_createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.renderPass = renderpass;
		m_createInfo.attachmentCount = 1;
		m_createInfo.width = device->getSurfaceData()->swapchainWidth;
		m_createInfo.height = device->getSurfaceData()->swapchainHeight;
		m_createInfo.layers = 1;
	}

	VK_Framebuffers::~VK_Framebuffers(){
		for (auto framebuffer : m_framebuffers) {
			vkDestroyFramebuffer(m_device->getDevice(), framebuffer, nullptr);
		}
	}

	void VK_Framebuffers::create(){
		for (int i = 0; i < m_framebuffers.size(); i++) {
			VkImageView attachments[] = {
				m_swapchain->getImage(i)
			};

			m_createInfo.pAttachments = attachments;

			if (vkCreateFramebuffer(m_device->getDevice(), &m_createInfo, nullptr, &m_framebuffers[i]) != VK_SUCCESS) {
				RenderSystem::LOGGER->error("Failed to create framebuffer.");
			}

			m_device->debug_setName(VK_OBJECT_TYPE_FRAMEBUFFER, (uint64_t)m_framebuffers[i],"Framebuffer");
		}
	}

}//end namespace