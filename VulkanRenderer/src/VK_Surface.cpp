#include "VK_Surface.h"

VK_Surface::VK_Surface(VkInstance instance, HWND windowHandle){
	m_instance = instance;
	m_windowHandle = windowHandle;
}

VK_Surface::~VK_Surface(){
	vkDestroySurfaceKHR(m_instance, surface, nullptr);
}

void VK_Surface::create(){
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.hwnd = m_windowHandle;
	createInfo.hinstance = GetModuleHandle(nullptr);

	CHECK_VK(vkCreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &surface), "Failed to create vulkan surface.");
}