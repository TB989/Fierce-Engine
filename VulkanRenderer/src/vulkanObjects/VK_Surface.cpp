#include "VK_Surface.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Surface::VK_Surface(VkInstance instance, HWND windowHandle) {
		m_instance = instance;
		m_windowHandle = windowHandle;

		m_createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.hwnd = m_windowHandle;
		m_createInfo.hinstance = GetModuleHandle(nullptr);
	}

	VK_Surface::~VK_Surface() {
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	}

	void VK_Surface::create() {
		if (vkCreateWin32SurfaceKHR(m_instance, &m_createInfo, nullptr, &m_surface) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create vulkan surface.");
		}
	}

}//end namespace