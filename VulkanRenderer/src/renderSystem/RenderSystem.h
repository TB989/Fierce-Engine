#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <windows.h>

#include "src/System.h"
#include "src/LoggingSystem.h"

namespace Fierce {

	class LoggingSystem;

	class UploadContext;

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

	class VK_Mesh;
	class VK_Texture;

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

		//########################### INTERFACE ##############################################################################
		int newMesh(int numVertices, int numIndices);
		void meshLoadVertices(int meshId,int numVertices,float* vertices);
		void meshLoadIndices(int meshId, int numIndices, uint16_t* indices);

		int newTexture(int width, int height, int numChannels);
		void textureLoadData(int textureId, unsigned char* pixels);

		void postInit();
		//########################### INTERFACE ##############################################################################

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

		UploadContext* m_uploadContext=nullptr;

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

		VK_DescriptorPool* m_descriptorPool = nullptr;

		Mat4* m_modelMatrix=nullptr;
		Mat4* m_viewMatrix=nullptr;
		Mat4* m_projMatrix=nullptr;

	private:
		int m_numMeshes = -1;
		std::vector<VK_Mesh*> m_meshes;

		int m_numTextures = -1;
		std::vector<VK_Texture*> m_textures;
	};

}//end namespace