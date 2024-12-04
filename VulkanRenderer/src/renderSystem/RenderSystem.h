#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <windows.h>

#include "src/System.h"
#include "src/LoggingSystem.h"

#include "src/manager/VK_Manager.h"

namespace Fierce {

	class LoggingSystem;

	class CoreContext;
	class UploadContext;

	class VK_Renderpass;
	class VK_Shader;
	class VK_Pipeline;
	class VK_Framebuffers;

	class VK_DescriptorPool;
	class VK_UBO;

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

		//void recreateSwapchain();

		//########################### INTERFACE ##############################################################################
		int newMesh(int numVertices, int numIndices);
		void meshLoadVertices(int meshId,int numVertices,float* vertices);
		void meshLoadIndices(int meshId, int numIndices, uint16_t* indices);

		int newTexture(int width, int height, int numChannels);
		void textureLoadData(int textureId, unsigned char* pixels);

		void postInit();
		//########################### INTERFACE ##############################################################################

	public:
		struct UBOs {
			VK_UBO* uboViewProjection;
			VK_UBO* uboModel;
		};

	public:
		static Logger* LOGGER;

	private:
		void createRenderpasses();
		void createFramebuffers();
		void createShaders();
		void createPipelines();

	private:
		LoggingSystem* m_loggingSystem=nullptr;
		HWND m_windowHandle=NULL;

		CoreContext* m_coreContext = nullptr;
		UploadContext* m_uploadContext=nullptr;

		//Managers
		VK_Manager<VK_Renderpass*>* m_renderpasses=nullptr;
		VK_Manager<VK_Shader*>* m_shaders=nullptr;
		VK_Manager<VK_Pipeline*>* m_pipelines=nullptr;
		VK_Manager<VK_Framebuffers*>* m_framebuffers=nullptr;

		const static int NUM_FRAMES_IN_FLIGHT = 2;
		UBOs ubos[NUM_FRAMES_IN_FLIGHT];

		VK_DescriptorPool* m_descriptorPoolViewProjection = nullptr;
		VK_DescriptorPool* m_descriptorPoolModel = nullptr;
		VK_DescriptorPool* m_descriptorPoolSampler = nullptr;

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