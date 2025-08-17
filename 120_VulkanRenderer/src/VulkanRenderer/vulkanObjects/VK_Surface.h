#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <windows.h>

namespace Fierce {

	class VK_Surface {
	public:
		VK_Surface(VkInstance instance, HWND windowHandle);
		~VK_Surface();

		void create();
		VkSurfaceKHR getId() { return m_surface; }

	private:
		//Create info
		VkWin32SurfaceCreateInfoKHR m_createInfo={};

		//Vulkan objects
		VkInstance m_instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;

		//Window handle
		HWND m_windowHandle = nullptr;
	};

}//end namespace