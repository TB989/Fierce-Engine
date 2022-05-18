#pragma once

#include "VK_Swapchain.h"

class VK_Instance;
class VK_Surface;
class VK_Device;

class VK_Context{
public:
	VK_Context(HWND windowHandle);
	~VK_Context();

	VK_Device* getDevice() { return device; }
	VK_Swapchain* getSwapchain() { return swapchain; }

	VkImageView getSwapchainImage(int index) { return swapchain->getImage(index); }
	int getNumSwapchainImages() { return swapchain->getNumImages(); }

private:
	VK_Instance* instance;
	VK_Surface* surface;
	VK_Device* device;
	VK_Swapchain* swapchain;
};