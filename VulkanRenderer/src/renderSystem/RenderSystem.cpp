#include "RenderSystem.h"

#include "uploading/UploadContext.h"

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>

#include <iostream>

#include "src/Matrix.h"

#include "vulkanObjects/VK_Instance.h"
#include "vulkanObjects/VK_Surface.h"
#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Swapchain.h"
#include "vulkanObjects/VK_Renderpass.h"
#include "vulkanObjects/VK_Shader.h"
#include "vulkanObjects/VK_Pipeline.h"
#include "vulkanObjects/VK_Framebuffers.h"
#include "vulkanObjects/VK_CommandBuffer.h"
#include "vulkanObjects/VK_Semaphore.h"
#include "vulkanObjects/VK_Fence.h"
#include "vulkanObjects/VK_Buffer.h"
#include "vulkanObjects/VK_DescriptorPool.h"
#include "vulkanObjects/VK_DescriptorSet.h"
#include "vulkanObjects/VK_Image.h"
#include "vulkanObjects//VK_ImageView.h"
#include "vulkanObjects/VK_Sampler.h"
#include "vulkanObjects/VK_UBO.h"

#include "assets/VK_Mesh.h"
#include "assets/VK_Texture.h"

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

		m_instance = new VK_Instance();
		m_instance->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_win32_surface" }));
		m_instance->addCheck(new VK_Check_Device_Extensions(false, { VK_EXT_DEBUG_UTILS_EXTENSION_NAME }));
		m_instance->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
		m_instance->create();
		//m_instance->printActiveExtensions();
		//m_instance->printActiveValidationLayers();

		m_surface = new VK_Surface(m_instance->getId(), m_windowHandle);
		m_surface->create();

		m_device = new VK_Device(m_instance, m_surface->getId());
		m_device->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SWAPCHAIN_EXTENSION_NAME }));
		m_device->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
		m_device->addCheck(new VK_Check_Device_General());
		m_device->addCheck(new VK_Check_Device_Queues());
		m_device->addCheck(new VK_Check_Device_Surface_Format({ VK_FORMAT_B8G8R8A8_SRGB }));
		m_device->addCheck(new VK_Check_Device_Surface_PresentMode({ VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR }));
		m_device->addCheck(new VK_Check_Sampler_Anisotropy());
		//m_device->printSupportedData(false, false, true, false, false, false, true, false);
		m_device->create();
		//m_device->printActiveData(false,false,true,false,false,false,true,false);

		m_uploadContext = new UploadContext(m_device);

		m_swapchain = new VK_Swapchain(m_device, m_surface->getId(),VK_NULL_HANDLE);
		m_swapchain->create();

		m_renderpass = new VK_Renderpass(m_device);
		m_renderpass->create();

		m_vertexShader = new VK_Shader(m_device);
		m_vertexShader->setSourceCode("fifthShader_vert.spv");
		m_vertexShader->create();
		m_fragmentShader = new VK_Shader(m_device);
		m_fragmentShader->setSourceCode("fifthShader_frag.spv");
		m_fragmentShader->create();

		m_pipeline = new VK_Pipeline(m_device,m_renderpass->getId());
		m_pipeline->addVertexShader(m_vertexShader->getId());
		m_pipeline->addFragmentShader(m_fragmentShader->getId());
		m_pipeline->create();

		m_framebuffers = new VK_Framebuffers(m_device,m_renderpass->getId(),m_swapchain);
		m_framebuffers->create();

		m_descriptorPoolViewProjection = new VK_DescriptorPool(m_device->getDevice());
		m_descriptorPoolViewProjection->addDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,NUM_FRAMES_IN_FLIGHT);
		m_descriptorPoolViewProjection->create();
		m_device->debug_setName(VK_OBJECT_TYPE_DESCRIPTOR_POOL, (uint64_t)m_descriptorPoolViewProjection->getId(), "DescriptorPool View/Projection");

		m_descriptorPoolModel = new VK_DescriptorPool(m_device->getDevice());
		m_descriptorPoolModel->addDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 200);
		m_descriptorPoolModel->create();
		m_device->debug_setName(VK_OBJECT_TYPE_DESCRIPTOR_POOL, (uint64_t)m_descriptorPoolModel->getId(), "DescriptorPool Model");

		m_descriptorPoolSampler = new VK_DescriptorPool(m_device->getDevice());
		m_descriptorPoolSampler->addDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 200);
		m_descriptorPoolSampler->create();
		m_device->debug_setName(VK_OBJECT_TYPE_DESCRIPTOR_POOL, (uint64_t)m_descriptorPoolSampler->getId(), "DescriptorPool Sampler");

		//Create per frame ressources
		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			framesData[i].commandBuffer = m_device->getCommandBuffer(VK_Device::GRAPHICS);
			framesData[i].commandBuffer->create();
			m_device->debug_setName(VK_OBJECT_TYPE_COMMAND_BUFFER, (uint64_t)framesData[i].commandBuffer->getId(), "CommandBuffer frame");

			framesData[i].uboViewProjection = new VK_UBO(m_device, 2*16 * sizeof(float), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			framesData[i].uboViewProjection->create();
			framesData[i].uboViewProjection->createDescriptorSet(m_descriptorPoolViewProjection, m_pipeline->getDescriptorSetLayoutViewProjection());
			m_device->debug_setName(VK_OBJECT_TYPE_BUFFER, (uint64_t)framesData[i].uboViewProjection->getId(), "Buffer UBO View/Projection");

			framesData[i].uboModel = new VK_UBO(m_device, 16 * sizeof(float), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			framesData[i].uboModel->create();
			framesData[i].uboModel->createDescriptorSet(m_descriptorPoolModel, m_pipeline->getDescriptorSetLayoutModel());
			m_device->debug_setName(VK_OBJECT_TYPE_BUFFER, (uint64_t)framesData[i].uboModel->getId(), "Buffer UBO Model");

			framesData[i].imageAvailableSemaphore = new VK_Semaphore(m_device->getDevice());
			framesData[i].imageAvailableSemaphore->create();
			m_device->debug_setName(VK_OBJECT_TYPE_SEMAPHORE, (uint64_t)framesData[i].imageAvailableSemaphore->getId(), "Semaphore imageAvailable");

			framesData[i].renderFinishedSemaphore = new VK_Semaphore(m_device->getDevice());
			framesData[i].renderFinishedSemaphore->create();
			m_device->debug_setName(VK_OBJECT_TYPE_SEMAPHORE, (uint64_t)framesData[i].renderFinishedSemaphore->getId(), "Semaphore renderFinished");

			framesData[i].renderFinishedFence = new VK_Fence(m_device->getDevice());
			framesData[i].renderFinishedFence->create();
			m_device->debug_setName(VK_OBJECT_TYPE_FENCE, (uint64_t)framesData[i].renderFinishedFence->getId(), "Fence renderFinished");
		}

		m_modelMatrix = new Mat4();
		m_modelMatrix->scale(100.0f, 100.0f, 1.0f);
		m_viewMatrix = new Mat4();
		m_projMatrix = new Mat4();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	void RenderSystem::updateSystem(){
		beginFrame();
		updateUniformBuffer();
		recordCommandBuffer();
		endFrame();
	}

	void RenderSystem::cleanUpSystem(){
		if (vkDeviceWaitIdle(m_device->getDevice())!=VK_SUCCESS) {
			LOGGER->error("Failed to wait for idle device.");
		}

		delete m_modelMatrix;
		delete m_viewMatrix;
		delete m_projMatrix;

		for (VK_Mesh* mesh:m_meshes) {
			delete mesh;
		}
		for (VK_Texture* texture : m_textures) {
			delete texture;
		}

		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			delete framesData[i].renderFinishedFence;
			delete framesData[i].renderFinishedSemaphore;
			delete framesData[i].imageAvailableSemaphore;
			delete framesData[i].uboViewProjection;
			delete framesData[i].uboModel;
			m_device->releaseCommandBuffer(framesData[i].commandBuffer);
		}

		delete m_descriptorPoolViewProjection;
		delete m_descriptorPoolModel;
		delete m_descriptorPoolSampler;

		delete m_framebuffers;
		delete m_pipeline;
		delete m_fragmentShader;
		delete m_vertexShader;
		delete m_renderpass;
		delete m_swapchain;

		delete m_uploadContext;

		delete m_device;
		delete m_surface;
		delete m_instance;
		m_loggingSystem->deleteLogger(LOGGER);
	}

	void RenderSystem::recordCommandBuffer(){
		FrameData& frameData = framesData[currentFrame];

		frameData.commandBuffer->startRecording();
		frameData.commandBuffer->beginRenderpass(m_renderpass->getId(), m_framebuffers->getFramebuffer(imageIndex));
		frameData.commandBuffer->bindPipeline(m_pipeline->getId());
		frameData.commandBuffer->setViewport(static_cast<float>(m_device->getSurfaceData()->swapchainWidth), static_cast<float>(m_device->getSurfaceData()->swapchainHeight));
		frameData.commandBuffer->setScissor(m_device->getSurfaceData()->swapchainWidth, m_device->getSurfaceData()->swapchainHeight);
		frameData.commandBuffer->bindDescriptorSet(m_pipeline, frameData.uboViewProjection->getDescriptorSet(), 0);
		frameData.commandBuffer->bindDescriptorSet(m_pipeline, frameData.uboModel->getDescriptorSet(), 1);
		frameData.commandBuffer->bindDescriptorSet(m_pipeline, m_textures[0]->getDescriptorSet(), 2);
		for (VK_Mesh* mesh:m_meshes) {
			frameData.commandBuffer->bindVertexBuffer(mesh->getVertexBuffer()->getId());
			frameData.commandBuffer->bindIndexBuffer(mesh->getIndexBuffer()->getId());
			frameData.commandBuffer->renderIndexed(mesh->getNumIndices());
		}
		frameData.commandBuffer->endRenderpass();
		frameData.commandBuffer->endRecording();
	}

	void RenderSystem::updateUniformBuffer(){
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		m_modelMatrix->rotateZ(0.01f);
		m_projMatrix->setToOrthographicProjection(false, (float)m_device->getSurfaceData()->swapchainWidth,(float)m_device->getSurfaceData()->swapchainHeight,0.0f,1.0f);

		FrameData& frameData = framesData[currentFrame];
		frameData.uboViewProjection->loadData(2*16 * sizeof(float),m_viewMatrix->get(), m_projMatrix->get());
		frameData.uboModel->loadData(16 * sizeof(float), m_modelMatrix->get());
	}

	void RenderSystem::recreateSwapchain(){
		if (vkDeviceWaitIdle(m_device->getDevice()) != VK_SUCCESS) {
			LOGGER->error("Failed to wait for idle device.");
		}

		m_device->requerySurfaceData();

		delete m_framebuffers;

		VK_Swapchain* oldSwapchain = m_swapchain;
		VK_Swapchain* newSwapchain = new VK_Swapchain(m_device,m_surface->getId(),oldSwapchain->getId());
		newSwapchain->create();
		m_swapchain = newSwapchain;
		delete oldSwapchain;

		m_framebuffers = new VK_Framebuffers(m_device,m_renderpass->getId(), m_swapchain);
		m_framebuffers->create();

		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			framesData[i].commandBuffer->updateRenderArea();
		}
	}

	int RenderSystem::newMesh(int numVertices,int numIndices){
		m_numMeshes++;
		m_meshes.push_back(new VK_Mesh(m_device, numVertices, numIndices));
		return m_numMeshes;
	}

	int RenderSystem::newTexture(int width, int height,int numChannels){
		m_numTextures++;
		m_textures.push_back(new VK_Texture(m_device, width,height,numChannels));
		return m_numTextures;
	}

	void RenderSystem::textureLoadData(int textureId, unsigned char* pixels){
		m_textures[textureId]->loadData(m_textures[textureId]->getSize(), pixels);
	}

	void RenderSystem::meshLoadVertices(int meshId, int numVertices, float* vertices){
		m_meshes[meshId]->loadVertices(numVertices,vertices);
	}

	void RenderSystem::meshLoadIndices(int meshId, int numIndices, uint16_t* indices){
		m_meshes[meshId]->loadIndices(numIndices, indices);
	}

	void RenderSystem::postInit(){
		for (VK_Mesh* mesh:m_meshes) {
			m_uploadContext->copyMesh(mesh);
		}
		for (VK_Texture* texture : m_textures) {
			m_uploadContext->copyTexture(texture);
		}
		m_uploadContext->startAndWaitForUpload();

		m_textures[0]->createImageViewAndSampler();
		m_textures[0]->createDescriptorSet(m_descriptorPoolSampler,m_pipeline->getDescriptorSetLayoutSampler());

		for (int i = 0; i < NUM_FRAMES_IN_FLIGHT; i++) {
			framesData[i].uboViewProjection->update(framesData[i].uboViewProjection);
			framesData[i].uboModel->update(framesData[i].uboModel);
			m_textures[0]->update(m_textures[0]->getImageView()->getId(), m_textures[0]->getSampler()->getId());
		}
	}

	void RenderSystem::beginFrame(){
		FrameData& frameData = framesData[currentFrame];
		VkFence fence = frameData.renderFinishedFence->getId();

		//Fences logic
		if (vkWaitForFences(m_device->getDevice(), 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS) {
			LOGGER->error("Failed to wait for fences.");
		}
		if (vkResetFences(m_device->getDevice(), 1, &fence)!=VK_SUCCESS) {
			LOGGER->error("Failed to reset fence.");
		}

		//Vk Acquire image
		VkResult result = vkAcquireNextImageKHR(m_device->getDevice(), m_swapchain->getId(), UINT64_MAX, frameData.imageAvailableSemaphore->getId(), VK_NULL_HANDLE, &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
		}
		else if (result != VK_SUBOPTIMAL_KHR && result != VK_SUCCESS) {
			LOGGER->error("Failed to aquire image.");
		}

		//Reset command buffer
		frameData.commandBuffer->reset();
	}

	void RenderSystem::endFrame(){
		FrameData& frameData = framesData[currentFrame];

		//Submit command buffer
		m_device->submitCommandBuffer(VK_Device::QUEUE_TYPE::GRAPHICS,frameData.commandBuffer->getId(), frameData.imageAvailableSemaphore->getId(), frameData.renderFinishedSemaphore->getId(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, frameData.renderFinishedFence->getId());

		//Present image
		VkSwapchainKHR swapchain = m_swapchain->getId();
		VkSemaphore semaphore = frameData.renderFinishedSemaphore->getId();

		VkPresentInfoKHR m_presentInfo = {};
		m_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		m_presentInfo.pNext = nullptr;
		m_presentInfo.pResults = nullptr;
		m_presentInfo.swapchainCount = 1;
		m_presentInfo.pSwapchains = &swapchain;
		m_presentInfo.pImageIndices = &imageIndex;
		m_presentInfo.waitSemaphoreCount = 1;
		m_presentInfo.pWaitSemaphores = &semaphore;
		VkResult result = vkQueuePresentKHR(m_device->getGraphicsQueue(), &m_presentInfo);
		if (result==VK_ERROR_OUT_OF_DATE_KHR||result==VK_SUBOPTIMAL_KHR) {
			recreateSwapchain();
		}
		else if (result!=VK_SUCCESS) {
			LOGGER->error("Failed to present image.");
		}

		//Update frame counter
		currentFrame = (currentFrame + 1) % NUM_FRAMES_IN_FLIGHT;
	}

}//end namespace