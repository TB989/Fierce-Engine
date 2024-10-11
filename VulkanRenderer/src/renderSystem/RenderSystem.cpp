#include "RenderSystem.h"

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
#include "vulkanObjects/VK_CommandPool.h"
#include "vulkanObjects/VK_CommandBuffer.h"
#include "vulkanObjects/VK_Semaphore.h"
#include "vulkanObjects/VK_Fence.h"
#include "vulkanObjects/VK_Buffer.h"
#include "vulkanObjects/VK_DescriptorPool.h"
#include "vulkanObjects/VK_DescriptorSet.h"
#include "vulkanObjects/VK_Image.h"
#include "vulkanObjects//VK_ImageView.h"
#include "vulkanObjects/VK_Sampler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "imageLoading/stb_image.h"

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

		m_device = new VK_Device(m_instance->getId(), m_surface->getId());
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

		//####################################################################################################################################
		float vertices[] = {
			-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,1.0f,0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,0.0f,0.0f,
			0.5f, 0.5f, 0.0f, 0.0f, 1.0f,0.0f,1.0f,
			-0.5f, 0.5f, 1.0f, 1.0f, 1.0f,1.0f,1.0f
		};

		uint16_t indices[] = {
			0, 2,1, 2, 0,3
		};
		//####################################################################################################################################

		m_swapchain = new VK_Swapchain(m_device, m_surface->getId(),VK_NULL_HANDLE);
		m_swapchain->create();

		m_renderpass = new VK_Renderpass(m_device);
		m_renderpass->create();

		m_vertexShader = new VK_Shader(m_device->getDevice());
		m_vertexShader->setSourceCode("fourthShader_vert.spv");
		m_vertexShader->create();
		m_fragmentShader = new VK_Shader(m_device->getDevice());
		m_fragmentShader->setSourceCode("fourthShader_frag.spv");
		m_fragmentShader->create();

		m_pipeline = new VK_Pipeline(m_device,m_renderpass->getId());
		m_pipeline->addVertexShader(m_vertexShader->getId());
		m_pipeline->addFragmentShader(m_fragmentShader->getId());
		m_pipeline->create();

		m_framebuffers = new VK_Framebuffers(m_device,m_renderpass->getId(),m_swapchain);
		m_framebuffers->create();

		m_commandPool = new VK_CommandPool(m_device);
		m_commandPool->create();
		m_copy_commandBuffer = new VK_CommandBuffer(m_device, m_commandPool->getId());
		m_copy_commandBuffer->create();

		m_dedicated_commandPool = new VK_CommandPool(m_device);
		m_dedicated_commandPool->bindToTransferQueue();
		m_dedicated_commandPool->create();
		m_dedicated_commandBuffer = new VK_CommandBuffer(m_device, m_dedicated_commandPool->getId());
		m_dedicated_commandBuffer->create();

		m_descriptorPool = new VK_DescriptorPool(m_device->getDevice());
		m_descriptorPool->addDescriptorType(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,NUM_FRAMES_IN_FLIGHT);
		m_descriptorPool->addDescriptorType(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NUM_FRAMES_IN_FLIGHT);
		m_descriptorPool->create();

		//Create per frame ressources
		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			framesData[i].commandBuffer = new VK_CommandBuffer(m_device, m_commandPool->getId());
			framesData[i].commandBuffer->create();

			framesData[i].ubo = new VK_Buffer(m_device, 3*16 * sizeof(float), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			framesData[i].ubo->create();

			framesData[i].descriptorSet = new VK_DescriptorSet(m_device->getDevice(),m_descriptorPool->getId(),m_pipeline);
			framesData[i].descriptorSet->create();

			framesData[i].imageAvailableSemaphore = new VK_Semaphore(m_device->getDevice());
			framesData[i].imageAvailableSemaphore->create();

			framesData[i].renderFinishedSemaphore = new VK_Semaphore(m_device->getDevice());
			framesData[i].renderFinishedSemaphore->create();

			framesData[i].renderFinishedFence = new VK_Fence(m_device->getDevice());
			framesData[i].renderFinishedFence->create();
		}

		//MESH/////////////////////////////////////////////////////////////////////////////////////////////////////
		m_vertexStagingBuffer = new VK_Buffer(m_device, 4*7 * sizeof(float), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_vertexStagingBuffer->create();
		m_vertexStagingBuffer->loadData(4*7 * sizeof(float),vertices);

		m_vertexBuffer = new VK_Buffer(m_device, 4*7 * sizeof(float), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_vertexBuffer->shareRessourcesWithTransferQueue();
		m_vertexBuffer->create();

		m_indexStagingBuffer = new VK_Buffer(m_device, 6 * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_indexStagingBuffer->create();
		m_indexStagingBuffer->loadData(6 * sizeof(uint16_t), indices);

		m_indexBuffer = new VK_Buffer(m_device, 6 * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_indexBuffer->shareRessourcesWithTransferQueue();
		m_indexBuffer->create();

		//IMAGE////////////////////////////////////////////////////////////////////////////////////////////////////
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/VulkanRenderer/res/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		VkDeviceSize imageSize = texWidth * texHeight * 4;

		if (!pixels) {
			RenderSystem::LOGGER->error("Unable to load image.");
		}

		m_imageStagingBuffer = new VK_Buffer(m_device, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_imageStagingBuffer->create();
		m_imageStagingBuffer->loadData(imageSize, pixels);

		stbi_image_free(pixels);

		m_image = new VK_Image(m_device, texWidth, texHeight, imageSize, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_image->shareRessourcesWithTransferQueue();
		m_image->create();

		//Record buffer
		m_dedicated_commandBuffer->startRecording();
		m_dedicated_commandBuffer->copy(m_vertexStagingBuffer->getId(),m_vertexBuffer->getId(), 4*7 * sizeof(float));
		m_dedicated_commandBuffer->copy(m_indexStagingBuffer->getId(), m_indexBuffer->getId(), 6 * sizeof(uint16_t));
		m_dedicated_commandBuffer->imageBarrier(m_image->getId(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		m_dedicated_commandBuffer->copy(m_imageStagingBuffer->getId(), m_image->getId(), texWidth,texHeight);
		//######## TODO #########: Do this on graphics queue 
		//m_dedicated_commandBuffer->imageBarrier(m_image->getId(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		m_dedicated_commandBuffer->endRecording();
		m_device->submitCommandBufferOnTransferQueue(m_dedicated_commandBuffer->getId(), VK_NULL_HANDLE, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);

		if (vkQueueWaitIdle(m_device->getTransferQueue()) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to wait for idle queue.");
		}

		m_uploadGraphicsBuffer = new VK_CommandBuffer(m_device,m_commandPool->getId());
		m_uploadGraphicsBuffer->create();
		m_uploadGraphicsBuffer->startRecording();
		m_uploadGraphicsBuffer->imageBarrier(m_image->getId(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		m_uploadGraphicsBuffer->endRecording();
		m_device->submitCommandBufferOnGraphicsQueue(m_uploadGraphicsBuffer->getId(), VK_NULL_HANDLE, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);

		if (vkQueueWaitIdle(m_device->getGraphicsQueue()) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to wait for idle queue.");
		}

		m_imageView = new VK_ImageView(m_device->getDevice(),m_image->getId());
		m_imageView->create();

		m_sampler = new VK_Sampler(m_device);
		m_sampler->create();

		for (int i = 0; i < NUM_FRAMES_IN_FLIGHT; i++) {
			framesData[i].descriptorSet->update(framesData[i].ubo,m_imageView->getId(),m_sampler->getId());
		}

		delete m_uploadGraphicsBuffer;

		delete m_indexStagingBuffer;
		delete m_vertexStagingBuffer;
		delete m_imageStagingBuffer;

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

		delete m_sampler;
		delete m_imageView;
		delete m_image;
		delete m_indexBuffer;
		delete m_vertexBuffer;

		delete m_copy_commandBuffer;

		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			delete framesData[i].renderFinishedFence;
			delete framesData[i].renderFinishedSemaphore;
			delete framesData[i].imageAvailableSemaphore;
			delete framesData[i].descriptorSet;
			delete framesData[i].ubo;
			delete framesData[i].commandBuffer;
		}

		delete m_descriptorPool;

		delete m_commandPool;

		delete m_dedicated_commandBuffer;
		delete m_dedicated_commandPool;

		delete m_framebuffers;
		delete m_pipeline;
		delete m_fragmentShader;
		delete m_vertexShader;
		delete m_renderpass;
		delete m_swapchain;
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
		frameData.commandBuffer->bindVertexBuffer(m_vertexBuffer->getId());
		frameData.commandBuffer->bindIndexBuffer(m_indexBuffer->getId());
		frameData.commandBuffer->setViewport(static_cast<float>(m_device->getSurfaceData()->swapchainWidth), static_cast<float>(m_device->getSurfaceData()->swapchainHeight));
		frameData.commandBuffer->setScissor(m_device->getSurfaceData()->swapchainWidth, m_device->getSurfaceData()->swapchainHeight);
		frameData.commandBuffer->bindDescriptorSet(m_pipeline,frameData.descriptorSet->getId());
		frameData.commandBuffer->renderIndexed(6);
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
		frameData.ubo->loadData(3*16 * sizeof(float),m_modelMatrix->get(), m_viewMatrix->get(), m_projMatrix->get());
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
		m_device->submitCommandBufferOnGraphicsQueue(frameData.commandBuffer->getId(), frameData.imageAvailableSemaphore->getId(), frameData.renderFinishedSemaphore->getId(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, frameData.renderFinishedFence->getId());

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