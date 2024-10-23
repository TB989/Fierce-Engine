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
	class VK_Framebuffers;
	class VK_CommandBuffer;
	class VK_Semaphore;
	class VK_Fence;
	class VK_Buffer;
	class VK_DescriptorPool;
	class VK_DescriptorSet;
	class VK_Image;
	class VK_ImageView;
	class VK_Sampler;

	class Mat4;

	class RenderSystem:public System {
	public:
		RenderSystem(LoggingSystem* loggingSystem);
		~RenderSystem();

		void setWindowHandle(HWND m_windowHandle);

		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

		void recordCommandBuffer();
		void updateUniformBuffer();

		void recreateSwapchain();

	public:
		struct FrameData {
			VK_CommandBuffer* commandBuffer;
			VK_Buffer* ubo;
			VK_DescriptorSet* descriptorSet;

			VK_Semaphore* imageAvailableSemaphore;
			VK_Semaphore* renderFinishedSemaphore;
			VK_Fence* renderFinishedFence;
		};

	public:
		static Logger* LOGGER;

	private:
		void beginFrame();
		void endFrame();

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
		VK_Framebuffers* m_framebuffers=nullptr;

		const static int NUM_FRAMES_IN_FLIGHT = 2;
		uint32_t imageIndex=0;
		int currentFrame = 0;
		FrameData framesData[NUM_FRAMES_IN_FLIGHT];

		//VK_CommandPool* m_commandPool=nullptr;
		//VK_CommandBuffer* m_copy_commandBuffer = nullptr;

		//VK_CommandPool* m_dedicated_commandPool = nullptr;
		VK_CommandBuffer* m_dedicated_commandBuffer = nullptr;

		VK_Buffer* m_vertexBuffer=nullptr;
		VK_Buffer* m_vertexStagingBuffer = nullptr;
		VK_Buffer* m_indexBuffer = nullptr;
		VK_Buffer* m_indexStagingBuffer = nullptr;

		VK_DescriptorPool* m_descriptorPool = nullptr;

		Mat4* m_modelMatrix=nullptr;
		Mat4* m_viewMatrix=nullptr;
		Mat4* m_projMatrix=nullptr;

		VK_CommandBuffer* m_uploadGraphicsBuffer=nullptr;
		VK_Buffer* m_imageStagingBuffer=nullptr;
		VK_Image* m_image=nullptr;
		VK_ImageView* m_imageView = nullptr;
		VK_Sampler* m_sampler=nullptr;
	};

}//end namespace