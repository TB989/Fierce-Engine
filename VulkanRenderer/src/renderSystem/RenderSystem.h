#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <windows.h>

#include "src/System.h"
#include "src/LoggingSystem.h"

namespace Fierce {

	class LoggingSystem;

	class VK_Instance;
	class VK_Surface;
	class VK_Device;
	class VK_Swapchain;
	class VK_Renderpass;
	class VK_Shader;
	class VK_Pipeline;

	class RenderSystem:public System {
	public:
		RenderSystem(LoggingSystem* loggingSystem);
		~RenderSystem();

		void setWindowHandle(HWND m_windowHandle);

		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

	public:
		static Logger* LOGGER;

	private:
		LoggingSystem* m_loggingSystem=nullptr;
		HWND m_windowHandle=NULL;

		VK_Instance* m_instance = nullptr;
		VK_Surface* m_surface = nullptr;
		VK_Device* m_device = nullptr;
		VK_Swapchain* m_swapchain = nullptr;
		VK_Renderpass* m_renderpass=nullptr;
		VK_Shader* m_vertexShader=nullptr;
		VK_Shader* m_fragmentShader = nullptr;
		VK_Pipeline* m_pipeline=nullptr;
	};

}//end namespace