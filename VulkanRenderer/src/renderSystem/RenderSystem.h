#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <windows.h>

#include "src/System.h"
#include "src/LoggingSystem.h"

#include "src/manager/VK_Manager.h"

#include "src/FierceStrings.h"

namespace Fierce {

	class LoggingSystem;

	class CoreContext;
	class UploadContext;

	class VK_Renderpass;
	class VK_Framebuffers;
	class VK_DescriptorPool;
	class VK_DescriptorSetLayout;
	class VK_Shader;
	class VK_Pipeline;

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
		void updateSystem() override {};
		void cleanUpSystem() override;

		//########################### INTERFACE ##############################################################################
		int newMesh(int numVertices, int numIndices);
		void meshLoadVertices(int meshId,int numVertices,float* vertices);
		void meshLoadIndices(int meshId, int numIndices, uint16_t* indices);

		int newTexture(int width, int height, int numChannels);
		void textureLoadData(int textureId, unsigned char* pixels);

		void bindPipeline(std::string name);
		void setOrthographicProjection(float* projectionMatrix);
		void setPerspectiveProjection(float* projectionMatrix);
		void setViewMatrix(float* viewMatrix);
		void loadModelMatrix(float* modelMatrix);
		void loadColor(float* color);

		void startFrame();
		void drawMesh(int m_meshId);
		void endFrame();

		void postInit();
		//########################### INTERFACE ##############################################################################

	public:
		static Logger* LOGGER;

	private:
		void createRenderpasses();
		void createFramebuffers();
		void createDescriptorPools();
		void createDescriptorSetLayouts();
		void createShaders();
		void createPipelines();
		void createUbos();

	private:
		const static int MAX_NUM_MODEL_MATRICES = 100;

		LoggingSystem* m_loggingSystem=nullptr;
		HWND m_windowHandle=NULL;

		//Contexts
		CoreContext* m_coreContext = nullptr;
		UploadContext* m_uploadContext=nullptr;

		//Managers
		//VK_Manager<VK_Renderpass*>* m_renderpasses=nullptr;
		//VK_Manager<VK_Framebuffers*>* m_framebuffers = nullptr;
		VK_Manager<VK_DescriptorPool*>* m_descriptorPools = nullptr;
		VK_Manager<VK_DescriptorSetLayout*>* m_descriptorSetLayouts = nullptr;
		VK_Manager<VK_Shader*>* m_shaders=nullptr;
		VK_Manager<VK_Pipeline*>* m_pipelines=nullptr;
		VK_Manager<VK_UBO*>* m_ubosViewProjection=nullptr;
		VK_Manager<VK_UBO*>* m_ubosModel=nullptr;

		uint32_t m_matrixIndex = 0;

	private:
		int m_numMeshes = -1;
		std::vector<VK_Mesh*> m_meshes;

		int m_numTextures = -1;
		std::vector<VK_Texture*> m_textures;
	};

}//end namespace