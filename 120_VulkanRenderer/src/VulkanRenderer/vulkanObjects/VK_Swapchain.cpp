#include "VK_Swapchain.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

namespace Fierce {

	class VK_Device;

	VK_Swapchain::VK_Swapchain(VK_Device* device, VkSurfaceKHR surface,VkSwapchainKHR oldSwapchain) {
		m_device = device;
		m_surface = surface;

		m_createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.surface = m_surface;
		m_createInfo.minImageCount = 0;
		m_createInfo.imageFormat = m_device->getSurfaceData()->swapchainFormat.format;
		m_createInfo.imageColorSpace = m_device->getSurfaceData()->swapchainFormat.colorSpace;
		m_createInfo.imageExtent = {};
		m_createInfo.imageArrayLayers = 1;
		m_createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		m_createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		m_createInfo.queueFamilyIndexCount = 0;
		m_createInfo.pQueueFamilyIndices = nullptr;
		m_createInfo.preTransform = m_device->getSurfaceData()->surfaceCapabilities.currentTransform;
		m_createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		m_createInfo.presentMode = m_device->getSurfaceData()->swapchainPresentMode;
		m_createInfo.clipped = VK_TRUE;
		m_createInfo.oldSwapchain = oldSwapchain;

		m_imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		m_imageViewCreateInfo.pNext = nullptr;
		m_imageViewCreateInfo.flags = 0;
		m_imageViewCreateInfo.image = 0;
		m_imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		m_imageViewCreateInfo.format = m_device->getSurfaceData()->swapchainFormat.format;
		m_imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		m_imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		m_imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		m_imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		m_imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		m_imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		m_imageViewCreateInfo.subresourceRange.levelCount = 1;
		m_imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		m_imageViewCreateInfo.subresourceRange.layerCount = 1;

		m_presentInfo={};
		m_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		m_presentInfo.pNext = nullptr;
		m_presentInfo.pResults = nullptr;
	}

	VK_Swapchain::~VK_Swapchain() {
		for (auto image : m_imageViews) {
			vkDestroyImageView(m_device->getDevice(), image, nullptr);
		}

		vkDestroySwapchainKHR(m_device->getDevice(), m_swapchain, nullptr);
	}

	void VK_Swapchain::create() {
		SurfaceData* surfaceData = m_device->getSurfaceData();
		m_extent = surfaceData->surfaceCapabilities.currentExtent;

		if (m_extent.width< surfaceData->surfaceCapabilities.minImageExtent.width) {
			m_extent.width = surfaceData->surfaceCapabilities.minImageExtent.width;
		}
		if (m_extent.width < surfaceData->surfaceCapabilities.maxImageExtent.width) {
			m_extent.width = surfaceData->surfaceCapabilities.maxImageExtent.width;
		}
		if (m_extent.height < surfaceData->surfaceCapabilities.minImageExtent.height) {
			m_extent.height = surfaceData->surfaceCapabilities.minImageExtent.height;
		}
		if (m_extent.height < surfaceData->surfaceCapabilities.maxImageExtent.height) {
			m_extent.height = surfaceData->surfaceCapabilities.maxImageExtent.height;
		}

		m_createInfo.imageExtent = m_extent;

		surfaceData->swapchainWidth = m_extent.width;
		surfaceData->swapchainHeight = m_extent.height;

		uint32_t imageCount = surfaceData->surfaceCapabilities.minImageCount + 1;
		if (surfaceData->surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceData->surfaceCapabilities.maxImageCount) {
			imageCount = surfaceData->surfaceCapabilities.maxImageCount;
		}
		m_createInfo.minImageCount = imageCount;

		if (vkCreateSwapchainKHR(m_device->getDevice(), &m_createInfo, nullptr, &m_swapchain)!=VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create swapchain.");
		}

		m_device->debug_setName(VK_OBJECT_TYPE_SWAPCHAIN_KHR, (uint64_t)m_swapchain, "Swapchain");

		if (vkGetSwapchainImagesKHR(m_device->getDevice(), m_swapchain, &imageCount, nullptr) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to get swapchain images.");
		}
		m_images.resize(imageCount);
		if (vkGetSwapchainImagesKHR(m_device->getDevice(), m_swapchain, &imageCount, m_images.data())!=VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to get swapchain images.");
		}

		m_imageViews.resize(m_images.size());
		for (size_t i = 0; i < m_imageViews.size(); i++) {
			m_imageViewCreateInfo.image = m_images[i];

			if (vkCreateImageView(m_device->getDevice(), &m_imageViewCreateInfo, nullptr, &m_imageViews[i])) {
				RenderSystem::LOGGER->error("Failed to create image view for swapchain.");
			}

			m_device->debug_setName(VK_OBJECT_TYPE_IMAGE, (uint64_t)m_images[i], "Swapchain image");
			m_device->debug_setName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_imageViews[i], "Swapchain image view");
		}
	}

}//end namespace