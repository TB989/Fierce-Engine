
#pragma once

#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include "src/utils/System.h"
#include "src/include/LoggingSystem.h"
#include "src/include/FileSystem.h"

#include "src/manager/VK_Manager.h"

#include "src/utils/FierceStrings.h"
#include "src/utils/Font.h"

#include "src/GraphicsContext.h"

namespace Fierce {

	class LoggingSystem;
	class FileSystem;

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

	class Mat4;

	class VK_Mesh;
	class VK_Texture;

	class RenderSystem:public System {
	public:
		RenderSystem(LoggingSystem* loggingSystem,FileSystem* fileSystem);
		~RenderSystem();

		void setWindowHandle(HWND m_windowHandle);

		void initSystem(std::string m_assetDirectory) override;
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
		void activateSampler(std::string pipeline, int texture);

		void startFrame();
		void drawMesh(int m_meshId);
		void endFrame();

		GraphicsContext* getGraphicsContext() { return (GraphicsContext*)m_graphicsContext; };
		void drawGraphicsContext();

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

		void loadAllFonts();
		void loadAllShaders();
		void loadAllTextures();

	private:
		const static int MAX_NUM_MODEL_MATRICES = 100;

		LoggingSystem* m_loggingSystem=nullptr;
		HWND m_windowHandle = NULL;
		FileSystem* m_fileSystem=nullptr;

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

		VK_Manager<Font*>* m_fonts = nullptr;

		uint32_t m_matrixIndex = 0;

	private:
		int m_numMeshes = -1;
		std::vector<VK_Mesh*> m_meshes;

		int m_numTextures = -1;
		std::vector<VK_Texture*> m_textures;
	};

}//end namespace