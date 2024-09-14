#pragma once

#include "vulkan/vulkan.h"

#include "VK_Device.h"

namespace Fierce {

	class VK_Swapchain {
	public:
		VK_Swapchain(VK_Device* device, VkSurfaceKHR surface);
		~VK_Swapchain();

		void create();
		VkSwapchainKHR getId() { return m_swapchain; }

		VkImageView getImage(int index) { return m_imageViews[index]; }
		size_t getNumImages() { return m_imageViews.size(); }

	private:
		//Create info
		VkExtent2D m_extent;
		VkSwapchainCreateInfoKHR m_createInfo={};
		VkImageViewCreateInfo m_imageViewCreateInfo={};

		//Vulkan objects
		VK_Device* m_device = nullptr;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;
		VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;

		//Images
		std::vector<VkImage> m_images;
		std::vector<VkImageView> m_imageViews;
	};

}//end namespace