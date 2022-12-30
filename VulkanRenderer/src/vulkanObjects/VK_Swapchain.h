#pragma once

#include "Common.h"
#include "VulkanObject.h"
#include "VK_Device.h"

class VK_Semaphore;

class VK_Swapchain :public VulkanObject{
public:
	VK_Swapchain(VK_Device* device, VkSurfaceKHR surface);
	~VK_Swapchain();

	void create();
	VkSwapchainKHR getSwapchain() { return m_swapchain; }

	VkImageView getImage(int index) { return images[index]; }
	size_t getNumImages() { return images.size(); }

	uint32_t getNextImageIndex(VK_Semaphore* signalSemaphore);
	void presentImage(uint32_t imageIndex, VK_Semaphore* waitSemaphore);

private:
	VK_Device* m_device = nullptr;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

	VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
	std::vector<VkImageView> images;
};