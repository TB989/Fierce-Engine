#include "RenderSystem.h"

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
		m_device->create();
		//m_device->printActiveData(true,true,true,true,true,true,true,true);

		m_swapchain = new VK_Swapchain(m_device, m_surface->getId(),VK_NULL_HANDLE);
		m_swapchain->create();

		m_renderpass = new VK_Renderpass(m_device);
		m_renderpass->create();

		m_vertexShader = new VK_Shader(m_device->getDevice());
		m_vertexShader->setSourceCode("firstShader_vert.spv");
		m_vertexShader->create();
		m_fragmentShader = new VK_Shader(m_device->getDevice());
		m_fragmentShader->setSourceCode("firstShader_frag.spv");
		m_fragmentShader->create();

		m_pipeline = new VK_Pipeline(m_device,m_renderpass->getId());
		m_pipeline->addVertexShader(m_vertexShader->getId());
		m_pipeline->addFragmentShader(m_fragmentShader->getId());
		m_pipeline->create();

		m_framebuffers = new VK_Framebuffers(m_device,m_renderpass->getId(),m_swapchain);
		m_framebuffers->create();

		//Create per frame ressources
		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			framesData[i].commandPool = new VK_CommandPool(m_device);
			framesData[i].commandPool->create();

			framesData[i].commandBuffer = new VK_CommandBuffer(m_device, framesData[i].commandPool->getId());
			framesData[i].commandBuffer->create();

			framesData[i].imageAvailableSemaphore = new VK_Semaphore(m_device->getDevice());
			framesData[i].imageAvailableSemaphore->create();

			framesData[i].renderFinishedSemaphore = new VK_Semaphore(m_device->getDevice());
			framesData[i].renderFinishedSemaphore->create();

			framesData[i].renderFinishedFence = new VK_Fence(m_device->getDevice());
			framesData[i].renderFinishedFence->create();
		}
	}

	void RenderSystem::updateSystem(){
		beginFrame();
		recordCommandBuffer();
		endFrame();
	}

	void RenderSystem::cleanUpSystem(){
		if (vkDeviceWaitIdle(m_device->getDevice())!=VK_SUCCESS) {
			LOGGER->error("Failed to wait for idle device.");
		}

		for (int i = 0;i<NUM_FRAMES_IN_FLIGHT;i++) {
			delete framesData[i].renderFinishedFence;
			delete framesData[i].renderFinishedSemaphore;
			delete framesData[i].imageAvailableSemaphore;
			delete framesData[i].commandBuffer;
			delete framesData[i].commandPool;
		}

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
		frameData.commandBuffer->setViewport(static_cast<float>(m_device->getSurfaceData()->swapchainWidth), static_cast<float>(m_device->getSurfaceData()->swapchainHeight));
		frameData.commandBuffer->setScissor(m_device->getSurfaceData()->swapchainWidth, m_device->getSurfaceData()->swapchainHeight);
		frameData.commandBuffer->render(3);
		frameData.commandBuffer->endRenderpass();
		frameData.commandBuffer->endRecording();
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
		m_device->submitCommandBuffer(frameData.commandBuffer->getId(), frameData.imageAvailableSemaphore->getId(), frameData.renderFinishedSemaphore->getId(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, frameData.renderFinishedFence->getId());

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
		VkResult result = vkQueuePresentKHR(m_device->getQueue(), &m_presentInfo);
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