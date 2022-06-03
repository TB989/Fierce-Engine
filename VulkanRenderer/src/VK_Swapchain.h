#pragma once

#include "Common.h"

#include "VK_Device.h"

class VK_Swapchain {
public:
	VK_Swapchain(VK_Device* device, VkSurfaceKHR surface);
	~VK_Swapchain();

	void create();
	VkSwapchainKHR getSwapchain() { return m_swapchain; }
	VkImageView getImage(int index) { return images[index]; }
	int getNumImages() { return images.size(); }

private:
	VK_Device* m_device = nullptr;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

	VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
	std::vector<VkImageView> images;
};