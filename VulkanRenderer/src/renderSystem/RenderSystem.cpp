#include "RenderSystem.h"

#include "src/core/CoreContext.h"
#include "src/uploading/UploadContext.h"
#include "src/graphicsContext/VulkanGraphicsContetxt.h"

#include "src/Matrix.h"

#include "src/vulkanObjects/VK_Renderpass.h"
#include "src/vulkanObjects/VK_Shader.h"
#include "src/vulkanObjects/VK_Pipeline.h"
#include "src/vulkanObjects/VK_Framebuffer.h"
#include "src/vulkanObjects/VK_CommandBuffer.h"
#include "src/vulkanObjects/VK_DescriptorPool.h"
#include "src/vulkanObjects/VK_Image.h"
#include "src/vulkanObjects/VK_ImageView.h"
#include "src/vulkanObjects/VK_Sampler.h"
#include "src/vulkanObjects/VK_UBO.h"

#include "src/assets/VK_Mesh.h"
#include "src/assets/VK_Texture.h"

#include "src/vulkanObjects/VK_DescriptorSetLayout.h"

namespace Fierce {

	Logger* RenderSystem::LOGGER = nullptr;

	RenderSystem::RenderSystem(LoggingSystem* loggingSystem){
		m_loggingSystem = loggingSystem;
	}

	RenderSystem::~RenderSystem(){}

	void RenderSystem::setWindowHandle(HWND windowHandle){
		m_windowHandle = windowHandle;
	}

	void RenderSystem::initSystem(){
		LOGGER = m_loggingSystem->createLogger("VK",true,"VULKAN");

		//Create managers
		m_descriptorPools = new VK_Manager<VK_DescriptorPool*>();
		m_descriptorSetLayouts = new VK_Manager<VK_DescriptorSetLayout*>();
		m_shaders = new VK_Manager<VK_Shader*>();
		m_pipelines = new VK_Manager<VK_Pipeline*>();
		m_ubosViewProjection = new VK_Manager<VK_UBO*>();
		m_ubosModel = new VK_Manager<VK_UBO*>();

		//Create contexts
		m_coreContext = new CoreContext(m_windowHandle);
		m_uploadContext = new UploadContext(m_coreContext->getDevice());
		m_graphicsContext = new VulkanGraphicsContext(m_coreContext->getDevice());

		for (int i = 0;i<m_coreContext->getNumFramebuffers();i++) {
			m_uploadContext->transitionImageLayout(m_coreContext->getFramebuffer(i)->getDepthBuffer()->getId(), VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
		}

		//Create engine ressources
		createRenderpasses();
		createFramebuffers();
		createDescriptorPools();
		createDescriptorSetLayouts();
		createShaders();
		createPipelines();
		createUbos();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	void RenderSystem::cleanUpSystem(){
		if (vkDeviceWaitIdle(m_coreContext->getDevice()->getDevice())!=VK_SUCCESS) {
			LOGGER->error("Failed to wait for idle device.");
		}

		for (VK_Mesh* mesh:m_meshes) {
			delete mesh;
		}
		for (VK_Texture* texture : m_textures) {
			delete texture;
		}

		//Delete engine ressources
		delete m_ubosViewProjection;
		delete m_ubosModel;
		delete m_pipelines;
		delete m_shaders;
		delete m_descriptorSetLayouts;
		delete m_descriptorPools;

		//Delete contexts
		delete m_graphicsContext;
		delete m_uploadContext;
		delete m_coreContext;

		m_loggingSystem->deleteLogger(LOGGER);
	}

	int RenderSystem::newMesh(int numVertices,int numIndices){
		m_numMeshes++;
		m_meshes.push_back(new VK_Mesh(m_coreContext->getDevice(), numVertices, numIndices));
		return m_numMeshes;
	}

	int RenderSystem::newTexture(int width, int height,int numChannels){
		m_numTextures++;
		m_textures.push_back(new VK_Texture(m_coreContext->getDevice(), width,height,numChannels));
		return m_numTextures;
	}

	void RenderSystem::textureLoadData(int textureId, unsigned char* pixels){
		m_textures[textureId]->loadData(m_textures[textureId]->getSize(), pixels);
	}

	void RenderSystem::bindPipeline(std::string name){
		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->bindPipeline(m_pipelines->get(name)->getId());
	}

	void RenderSystem::setOrthographicProjection(float* projectionMatrix){
		for (int i = 0;i<m_coreContext->getNumFramesInFlight();i++) {
			//Orthographic projection matrix at index 2
			m_ubosViewProjection->get(i)->loadData(16 * sizeof(float), 2,projectionMatrix);
		}
	}

	void RenderSystem::setPerspectiveProjection(float* projectionMatrix){
		for (int i = 0; i < m_coreContext->getNumFramesInFlight(); i++) {
			//Perspective projection matrix at index 0
			m_ubosViewProjection->get(i)->loadData(16 * sizeof(float), 0, projectionMatrix);
		}
	}

	void RenderSystem::setViewMatrix(float* viewMatrix){
		//View matrix at index 1
		m_ubosViewProjection->get(m_coreContext->getCurrentFrame())->loadData(16 * sizeof(float), 1, viewMatrix);
	}

	void RenderSystem::loadModelMatrix(float* modelMatrix){
		m_ubosModel->get(m_coreContext->getCurrentFrame())->loadData(16 * sizeof(float), m_matrixIndex,modelMatrix);

		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->pushConstants(m_pipelines->get("Main"), VK_SHADER_STAGE_VERTEX_BIT, sizeof(uint32_t),4*sizeof(float), & m_matrixIndex);

		m_matrixIndex++;
	}

	void RenderSystem::loadColor(float* color){
		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->pushConstants(m_pipelines->get("Main"), VK_SHADER_STAGE_VERTEX_BIT, 4*sizeof(float),0, color);
	}

	void RenderSystem::activateSampler(std::string pipeline,int texture){
		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->bindDescriptorSet(m_pipelines->get("Font"), m_textures[texture]->getDescriptorSet(), 2);
	}

	void RenderSystem::startFrame(){
		m_matrixIndex = 0;

		m_coreContext->beginFrame();

		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->startRecording();
		if (m_coreContext->getRenderpass()->hasDepthBuffer()) {
			commandBuffer->beginRenderpass(m_coreContext->getRenderpass()->getId(), m_coreContext->getActiveFramebuffer()->getId(),true);
		}
		else {
			commandBuffer->beginRenderpass(m_coreContext->getRenderpass()->getId(), m_coreContext->getActiveFramebuffer()->getId(),false);
		}
		commandBuffer->setViewport(m_coreContext->getSwapchainWidth(), m_coreContext->getSwapchainHeight());
		commandBuffer->setScissor(m_coreContext->getSwapchainWidth(), m_coreContext->getSwapchainHeight());
		commandBuffer->bindDescriptorSet(m_pipelines->get("Main"), m_ubosViewProjection->get(m_coreContext->getCurrentFrame())->getDescriptorSet(), 0);
		commandBuffer->bindDescriptorSet(m_pipelines->get("Main"), m_ubosModel->get(m_coreContext->getCurrentFrame())->getDescriptorSet(), 1);
	}

	void RenderSystem::meshLoadVertices(int meshId, int numVertices, float* vertices){
		m_meshes[meshId]->loadVertices(numVertices,vertices);
	}

	void RenderSystem::meshLoadIndices(int meshId, int numIndices, uint16_t* indices){
		m_meshes[meshId]->loadIndices(numIndices, indices);
	}

	void RenderSystem::drawMesh(int meshId){
		VK_Mesh* mesh = m_meshes[meshId];

		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->bindVertexBuffer(mesh->getVertexBuffer()->getId());
		commandBuffer->bindIndexBuffer(mesh->getIndexBuffer()->getId());
		commandBuffer->renderIndexed(mesh->getNumIndices());
	}

	void RenderSystem::endFrame(){
		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->endRenderpass();
		commandBuffer->endRecording();

		m_coreContext->endFrame();

		m_graphicsContext->reset();
	}

	void RenderSystem::drawGraphicsContext(){
		VK_CommandBuffer* commandBuffer = m_coreContext->getActiveCommandBuffer();
		commandBuffer->bindDescriptorSet(m_pipelines->get("GUI"), m_ubosViewProjection->get(m_coreContext->getCurrentFrame())->getDescriptorSet(), 0);
		commandBuffer->bindVertexBuffer(m_graphicsContext->getVertexBuffer()->getId());
		commandBuffer->bindIndexBuffer(m_graphicsContext->getIndexBuffer()->getId());
		commandBuffer->renderIndexed(m_graphicsContext->getNumIndices());
	}

	void RenderSystem::postInit(){
		//Upload everything
		for (VK_Mesh* mesh:m_meshes) {
			m_uploadContext->copyMesh(mesh);
		}
		for (VK_Texture* texture : m_textures) {
			m_uploadContext->copyTexture(texture);
		}
		m_uploadContext->startAndWaitForUpload();

		//Finish textures
		for (VK_Texture* texture:m_textures) {
			texture->createImageViewAndSampler();
			texture->createDescriptorSet(m_descriptorPools->get("Sampler"), m_descriptorSetLayouts->get("Sampler")->getId());
			texture->update(texture->getImageView()->getId(), texture->getSampler()->getId());
		}

		//Finish UBOs and textures
		for (int i = 0;i<m_coreContext->getNumFramesInFlight();i++) {
			m_ubosViewProjection->get(i)->update(m_ubosViewProjection->get(i));
			m_ubosModel->get(i)->update(m_ubosModel->get(i));
		}
	}

	void RenderSystem::createRenderpasses(){
		RenderSystem::LOGGER->info("##### Creating renderpasses #####");
		
		RenderSystem::LOGGER->info("##### Done creating renderpasses #####");
	}

	void RenderSystem::createFramebuffers(){
		RenderSystem::LOGGER->info("##### Creating framebuffers #####");
		
		RenderSystem::LOGGER->info("##### Done creating framebuffers #####");
	}

	void RenderSystem::createDescriptorPools(){
		RenderSystem::LOGGER->info("##### Creating descriptor pools #####");
		VK_DescriptorPool* descriptorPool = nullptr;

		descriptorPool = new VK_DescriptorPool(m_coreContext->getDevice()->getDevice());
		descriptorPool->addDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_coreContext->getNumFramesInFlight());
		descriptorPool->create();
		m_coreContext->getDevice()->debug_setName(VK_OBJECT_TYPE_DESCRIPTOR_POOL, (uint64_t)descriptorPool->getId(), "DescriptorPool Projection");
		m_descriptorPools->add("Projection",descriptorPool);

		descriptorPool = new VK_DescriptorPool(m_coreContext->getDevice()->getDevice());
		descriptorPool->addDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, m_coreContext->getNumFramesInFlight());
		descriptorPool->create();
		m_coreContext->getDevice()->debug_setName(VK_OBJECT_TYPE_DESCRIPTOR_POOL, (uint64_t)descriptorPool->getId(), "DescriptorPool Model");
		m_descriptorPools->add("Model",descriptorPool);

		descriptorPool = new VK_DescriptorPool(m_coreContext->getDevice()->getDevice());
		descriptorPool->addDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 200);
		descriptorPool->create();
		m_coreContext->getDevice()->debug_setName(VK_OBJECT_TYPE_DESCRIPTOR_POOL, (uint64_t)descriptorPool->getId(), "DescriptorPool Sampler");
		m_descriptorPools->add("Sampler",descriptorPool);
		RenderSystem::LOGGER->info("##### Done creating descriptor pools #####");
	}

	void RenderSystem::createDescriptorSetLayouts(){
		RenderSystem::LOGGER->info("##### Creating descriptor set layouts #####");
		VK_DescriptorSetLayout* descriptorSetLayout = nullptr;

		descriptorSetLayout = new VK_DescriptorSetLayout(m_coreContext->getDevice()->getDevice());
		descriptorSetLayout->addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1, VK_SHADER_STAGE_VERTEX_BIT);
		descriptorSetLayout->create();
		m_descriptorSetLayouts->add("Projection",descriptorSetLayout);

		descriptorSetLayout = new VK_DescriptorSetLayout(m_coreContext->getDevice()->getDevice());
		descriptorSetLayout->addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT);
		descriptorSetLayout->create();
		m_descriptorSetLayouts->add("Model", descriptorSetLayout);

		descriptorSetLayout = new VK_DescriptorSetLayout(m_coreContext->getDevice()->getDevice());
		descriptorSetLayout->addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT);
		descriptorSetLayout->create();
		m_descriptorSetLayouts->add("Sampler", descriptorSetLayout);
		RenderSystem::LOGGER->info("##### Done creating descriptor set layouts #####");
	}

	void RenderSystem::createShaders(){
		RenderSystem::LOGGER->info("##### Creating shaders #####");
		VK_Shader* shader = nullptr;

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Flat_Color_2D_vert.spv");
		shader->create();
		m_shaders->add("Shader_Flat_Color_2D_vert.spv",shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Flat_Color_2D_frag.spv");
		shader->create();
		m_shaders->add("Shader_Flat_Color_2D_frag.spv",shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Flat_Color_3D_vert.spv");
		shader->create();
		m_shaders->add("Shader_Flat_Color_3D_vert.spv", shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Flat_Color_3D_frag.spv");
		shader->create();
		m_shaders->add("Shader_Flat_Color_3D_frag.spv", shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Font_vert.spv");
		shader->create();
		m_shaders->add("Shader_Font_vert.spv", shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Font_frag.spv");
		shader->create();
		m_shaders->add("Shader_Font_frag.spv", shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Flat_Color_GUI_vert.spv");
		shader->create();
		m_shaders->add("Shader_Flat_Color_GUI_vert.spv", shader);

		shader = new VK_Shader(m_coreContext->getDevice());
		shader->setSourceCode("Shader_Flat_Color_GUI_frag.spv");
		shader->create();
		m_shaders->add("Shader_Flat_Color_GUI_frag.spv", shader);

		RenderSystem::LOGGER->info("##### Done creating shaders #####");
	}

	void RenderSystem::createPipelines(){
		RenderSystem::LOGGER->info("##### Creating pipelines #####");
		VK_Pipeline* pipeline = nullptr;

		pipeline = new VK_Pipeline(m_coreContext->getDevice(), m_coreContext->getRenderpass()->getId());
		pipeline->addVertexShader(m_shaders->get("Shader_Flat_Color_2D_vert.spv")->getId());
		pipeline->addFragmentShader(m_shaders->get("Shader_Flat_Color_2D_frag.spv")->getId());
		pipeline->addVertexInput(0, VK_FORMAT_R32G32_SFLOAT);
		//pipeline->addVertexInput(1, VK_FORMAT_R32G32B32_SFLOAT);
		//pipeline->addVertexInput(2, VK_FORMAT_R32G32_SFLOAT);
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Projection")->getId());
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Model")->getId());
		//pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Sampler")->getId());
		pipeline->addPushConstantRange(VK_SHADER_STAGE_VERTEX_BIT, 4 * sizeof(float)+sizeof(uint32_t), 0);
		//pipeline->addPushConstantRange(VK_SHADER_STAGE_VERTEX_BIT,sizeof(uint32_t), 4*sizeof(float));
		pipeline->create();
		m_pipelines->add("Main",pipeline);

		pipeline = new VK_Pipeline(m_coreContext->getDevice(), m_coreContext->getRenderpass()->getId());
		pipeline->addVertexShader(m_shaders->get("Shader_Flat_Color_3D_vert.spv")->getId());
		pipeline->addFragmentShader(m_shaders->get("Shader_Flat_Color_3D_frag.spv")->getId());
		pipeline->addVertexInput(0, VK_FORMAT_R32G32B32_SFLOAT);
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Projection")->getId());
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Model")->getId());
		pipeline->addPushConstantRange(VK_SHADER_STAGE_VERTEX_BIT, 4 * sizeof(float) + sizeof(uint32_t), 0);
		pipeline->addDepthTest();
		pipeline->create();
		m_pipelines->add("Main3D", pipeline);

		pipeline = new VK_Pipeline(m_coreContext->getDevice(), m_coreContext->getRenderpass()->getId());
		pipeline->addVertexShader(m_shaders->get("Shader_Font_vert.spv")->getId());
		pipeline->addFragmentShader(m_shaders->get("Shader_Font_frag.spv")->getId());
		pipeline->addVertexInput(0, VK_FORMAT_R32G32_SFLOAT);
		pipeline->addVertexInput(1, VK_FORMAT_R32G32_SFLOAT);
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Projection")->getId());
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Model")->getId());
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Sampler")->getId());
		pipeline->addPushConstantRange(VK_SHADER_STAGE_VERTEX_BIT, 4 * sizeof(float) + sizeof(uint32_t), 0);
		pipeline->enableBlending();
		pipeline->create();
		m_pipelines->add("Font", pipeline);

		pipeline = new VK_Pipeline(m_coreContext->getDevice(), m_coreContext->getRenderpass()->getId());
		pipeline->addVertexShader(m_shaders->get("Shader_Flat_Color_GUI_vert.spv")->getId());
		pipeline->addFragmentShader(m_shaders->get("Shader_Flat_Color_GUI_frag.spv")->getId());
		pipeline->addVertexInput(0, VK_FORMAT_R32G32_SFLOAT);
		pipeline->addVertexInput(1, VK_FORMAT_R32G32B32_SFLOAT);
		pipeline->addDescriptorSetLayout(m_descriptorSetLayouts->get("Projection")->getId());
		pipeline->create();
		m_pipelines->add("GUI", pipeline);

		RenderSystem::LOGGER->info("##### Done creating pipelines #####");
	}

	void RenderSystem::createUbos(){
		RenderSystem::LOGGER->info("##### Creating UBOs #####");
		VK_UBO* ubo = nullptr;

		for (int i = 0;i<m_coreContext->getNumFramesInFlight();i++) {
			//Projection
			ubo = new VK_UBO(m_coreContext->getDevice(), 3*16 * sizeof(float), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			ubo->create();
			ubo->createDescriptorSet(m_descriptorPools->get("Projection"), m_descriptorSetLayouts->get("Projection")->getId());
			m_coreContext->getDevice()->debug_setName(VK_OBJECT_TYPE_BUFFER, (uint64_t)ubo->getId(), "Buffer UBO Projection");
			m_ubosViewProjection->add("Projection",ubo);

			//Model
			ubo = new VK_UBO(m_coreContext->getDevice(), MAX_NUM_MODEL_MATRICES*16 * sizeof(float), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			ubo->create();
			ubo->createDescriptorSet(m_descriptorPools->get("Model"), m_descriptorSetLayouts->get("Model")->getId());
			m_coreContext->getDevice()->debug_setName(VK_OBJECT_TYPE_BUFFER, (uint64_t)ubo->getId(), "Buffer UBO Model");
			m_ubosModel->add("Model",ubo);
		}
		RenderSystem::LOGGER->info("##### Done creating UBOs #####");
	}

}//end namespace