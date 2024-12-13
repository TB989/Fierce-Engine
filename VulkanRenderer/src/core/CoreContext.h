#pragma once

#include "vulkan/vulkan.h"

#include <windows.h>

#include "src/manager/VK_Manager.h"

#include "src/vulkanObjects/VK_Device.h"

namespace Fierce {

	class VK_Instance;
	class VK_Surface;
	class VK_Swapchain;

	class VK_CommandBuffer;
	class VK_Semaphore;
	class VK_Fence;

	class VK_Framebuffers;
	class VK_Renderpass;

	class CoreContext {
	public:
		CoreContext(HWND windowHandle);
		~CoreContext();

		VK_Device* getDevice() { return m_device; }
		VK_CommandBuffer* getActiveCommandBuffer() { return framesData[currentFrame].commandBuffer; }
		uint32_t getActiveImageIndex() { return imageIndex; }
		int getCurrentFrame() { return currentFrame; }
		float getSwapchainWidth() { return static_cast<float>(m_device->getSurfaceData()->swapchainWidth); }
		float getSwapchainHeight() { return static_cast<float>(m_device->getSurfaceData()->swapchainHeight); }
		void linkFramebuffersManager(VK_Manager<VK_Framebuffers*>* manager1, VK_Manager<VK_Renderpass*>* manager2) { m_managerFramebuffers = manager1; m_managerRenderpass = manager2;}
		VK_Swapchain* getSwapchain() { return m_swapchain; }
		int getNumFramesInFlight() { return NUM_FRAMES_IN_FLIGHT; }

		void beginFrame();
		void endFrame();

	private:
		void createCoreRessources(HWND windowHandle);
		void createPerFrameRessources();

		void recreateSwapchain();

	private:
		struct FrameData {
			VK_CommandBuffer* commandBuffer=nullptr;

			VK_Semaphore* imageAvailableSemaphore=nullptr;
			VK_Semaphore* renderFinishedSemaphore=nullptr;
			VK_Fence* renderFinishedFence=nullptr;
		};

	private:
		const static int NUM_FRAMES_IN_FLIGHT = 2;

		VK_Instance* m_instance = nullptr;
		VK_Surface* m_surface = nullptr;
		VK_Device* m_device = nullptr;
		VK_Swapchain* m_swapchain = nullptr;

		uint32_t imageIndex = 0;
		int currentFrame = 0;
		FrameData framesData[NUM_FRAMES_IN_FLIGHT];

		VK_Manager<VK_Framebuffers*>* m_managerFramebuffers = nullptr;
		VK_Manager<VK_Renderpass*>* m_managerRenderpass = nullptr;
	};
}//end namespace
