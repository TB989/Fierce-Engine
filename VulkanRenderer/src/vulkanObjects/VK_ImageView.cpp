#include "VK_ImageView.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	VK_ImageView::VK_ImageView(VkDevice device, VkImage image,VkFormat format,VkImageAspectFlags aspectFlags){
		m_device = device;
		m_image = image;

		m_createInfo = {};
		m_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.image = m_image;
		m_createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		m_createInfo.format = format;
		m_createInfo.subresourceRange.aspectMask = aspectFlags;
		m_createInfo.subresourceRange.baseMipLevel = 0;
		m_createInfo.subresourceRange.levelCount = 1;
		m_createInfo.subresourceRange.baseArrayLayer = 0;
		m_createInfo.subresourceRange.layerCount = 1;
	}

	VK_ImageView::~VK_ImageView(){
		vkDestroyImageView(m_device, m_imageView, nullptr);
	}

	void VK_ImageView::create(){
		if (vkCreateImageView(m_device, &m_createInfo, nullptr, &m_imageView) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create image view.");
		}
	}

}//end namespace