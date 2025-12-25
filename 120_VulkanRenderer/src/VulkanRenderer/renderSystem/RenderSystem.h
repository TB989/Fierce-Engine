#pragma once

#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include "src/systems/IRenderSystem.h"
#include "src/systems/ILoggingSystem.h"

#include "src/VulkanRenderer/manager/VK_Manager.h"

#include "src/GUI/GraphicsContext.h"

namespace Fierce {

	class ILoggingSystem;
	class IFileSystem;
	class IParsingSystem;

	class CoreContext;
	class UploadContext;

	class VK_Renderpass;
	class VK_Framebuffers;
	class VK_DescriptorPool;
	class VK_DescriptorSetLayout;
	class VK_Shader;
	class VK_Pipeline;
	class VK_UBO;
	class VulkanGraphicsContext;

	class IMat4;

	class VK_Mesh;
	class VK_Texture;

	class RenderSystem:public IRenderSystem {
	public:
		RenderSystem();
		~RenderSystem();

		void setWindowHandle(HWND m_windowHandle);

		void initSystem(std::string m_assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override {};
		void cleanUpSystem() override;

		std::string getName() override;

		//########################### INTERFACE ##############################################################################
		int newMesh(int numVertices, int numIndices) override;
		void meshLoadVertices(int meshId,int numVertices,float* vertices) override;
		void meshLoadIndices(int meshId, int numIndices, uint16_t* indices) override;

		int newTexture(int width, int height, int numChannels) override;
		void textureLoadData(int textureId, unsigned char* pixels) override;

		void bindPipeline(std::string name) override;
		void setOrthographicProjection(float* projectionMatrix) override;
		void setPerspectiveProjection(float* projectionMatrix) override;
		void setViewMatrix(float* viewMatrix) override;
		void loadModelMatrix(float* modelMatrix) override;
		void loadColor(float* color) override;
		void activateSampler(std::string pipeline, int texture) override;

		void startFrame() override;
		void drawMesh(int m_meshId) override;
		void endFrame() override;

		GraphicsContext* getGraphicsContext() { return (GraphicsContext*)m_graphicsContext; };
		void resetGraphicsContext();
		void drawGraphicsContext();

		void postInit() override;
		//########################### INTERFACE ##############################################################################

	public:
		static ILogger* LOGGER;

	private:
		void createRenderpasses();
		void createFramebuffers();
		void createDescriptorPools();
		void createDescriptorSetLayouts();
		void createShaders();
		void createPipelines();
		void createUbos();

		void loadAllFonts();
		void loadAllShaders();
		void loadAllTextures();

	private:
		const static int MAX_NUM_MODEL_MATRICES = 100;

		ILoggingSystem* m_loggingSystem=nullptr;
		HWND m_windowHandle = NULL;
		IFileSystem* m_fileSystem=nullptr;

		IParsingSystem* m_parsingSystem=nullptr;
		std::string m_assetDirectory = "";
		std::string m_shaderDirectory = "";
		std::string m_fontDirectory = "";
		std::string m_textureDirectory = "";

		//Contexts
		CoreContext* m_coreContext = nullptr;
		UploadContext* m_uploadContext=nullptr;
		VulkanGraphicsContext* m_graphicsContext = nullptr;

		//Managers
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