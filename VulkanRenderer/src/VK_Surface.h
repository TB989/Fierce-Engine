#pragma once

#include "Common.h"

class VK_Surface{
public:
	VK_Surface(VkInstance instance, HWND windowHandle);
	~VK_Surface();

	void create();
	VkSurfaceKHR getId() { return surface; }

private:
	VkInstance m_instance=VK_NULL_HANDLE;
	HWND m_windowHandle = nullptr;
	VkSurfaceKHR surface=VK_NULL_HANDLE;
};