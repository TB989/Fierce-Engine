#include "VK_Framebuffer.h"

#include "src/VulkanRenderer/vulkanObjects/VK_Device.h"
#include "src/VulkanRenderer/vulkanObjects/VK_Image.h"
#include "src/VulkanRenderer/vulkanObjects/VK_ImageView.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Framebuffer::VK_Framebuffer(VK_Device* device,VkRenderPass renderpass){
		m_device = device;
		m_renderpass = renderpass;

		m_createInfo={};
		m_createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.renderPass = renderpass;
		m_createInfo.width = device->getSurfaceData()->swapchainWidth;
		m_createInfo.height = device->getSurfaceData()->swapchainHeight;
		m_createInfo.layers = 1;
	}

	VK_Framebuffer::~VK_Framebuffer(){
		vkDestroyFramebuffer(m_device->getDevice(), m_framebuffer, nullptr);

		if (m_depthBufferView!=nullptr) {
			delete m_depthBufferView;
		}
		if (m_depthBuffer != nullptr) {
			delete m_depthBuffer;
		}
	}

	void VK_Framebuffer::addAttachment(VkImageView imageView){
		m_attachments.push_back(imageView);
	}

	void VK_Framebuffer::addDepthBuffer(){
		m_depthBuffer = new VK_Image(m_device, m_device->getSurfaceData()->swapchainWidth, m_device->getSurfaceData()->swapchainHeight, 0, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_device->getSurfaceData()->depthFormat, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
		m_depthBuffer->shareRessourcesWithTransferQueue();
		m_depthBuffer->create();

		m_depthBufferView = new VK_ImageView(m_device->getDevice(), m_depthBuffer->getId(), m_device->getSurfaceData()->depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
		m_depthBufferView->create();

		m_attachments.push_back(m_depthBufferView->getId());


	}

	void VK_Framebuffer::create(){
		m_createInfo.attachmentCount = static_cast<uint32_t>(m_attachments.size());
		m_createInfo.pAttachments = m_attachments.data();

		if (vkCreateFramebuffer(m_device->getDevice(), &m_createInfo, nullptr, &m_framebuffer) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create framebuffer.");
		}

		m_device->debug_setName(VK_OBJECT_TYPE_FRAMEBUFFER, (uint64_t)m_framebuffer, "Framebuffer");
	}

}//end namespace