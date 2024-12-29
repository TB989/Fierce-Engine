#include "CoreContext.h"

#include "src/vulkanObjects/VK_Instance.h"
#include "src/vulkanObjects/VK_Surface.h"
#include "src/vulkanObjects/VK_Swapchain.h"

#include "src/vulkanObjects/VK_CommandBuffer.h"
#include "src/vulkanObjects/VK_Semaphore.h"
#include "src/vulkanObjects/VK_Fence.h"

#include "src/vulkanObjects/VK_Framebuffers.h"
#include "src/vulkanObjects/VK_Renderpass.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	CoreContext::CoreContext(HWND windowHandle) {
		createCoreRessources(windowHandle);
		createPerFrameRessources();
	}

	CoreContext::~CoreContext() {
		for (int i = 0; i < NUM_FRAMES_IN_FLIGHT; i++) {
			delete framesData[i].renderFinishedFence;
			delete framesData[i].renderFinishedSemaphore;
			delete framesData[i].imageAvailableSemaphore;
			m_device->releaseCommandBuffer(framesData[i].commandBuffer);
		}

		delete m_swapchain;
		delete m_device;
		delete m_surface;
		delete m_instance;
	}

	void CoreContext::beginFrame(){
		FrameData& frameData = framesData[currentFrame];
		VkFence fence = frameData.renderFinishedFence->getId();

		//Fences logic
		if (vkWaitForFences(m_device->getDevice(), 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to wait for fences.");
		}
		if (vkResetFences(m_device->getDevice(), 1, &fence) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to reset fence.");
		}

		//Vk Acquire image
		VkResult result = vkAcquireNextImageKHR(m_device->getDevice(), m_swapchain->getId(), UINT64_MAX, frameData.imageAvailableSemaphore->getId(), VK_NULL_HANDLE, &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapchain();
		}
		else if (result != VK_SUBOPTIMAL_KHR && result != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to aquire image.");
		}

		//Reset command buffer
		frameData.commandBuffer->reset();
	}

	void CoreContext::endFrame(){
		FrameData& frameData = framesData[currentFrame];

		//Submit command buffer
		m_device->submitCommandBuffer(VK_Device::QUEUE_TYPE::GRAPHICS, frameData.commandBuffer->getId(), frameData.imageAvailableSemaphore->getId(), frameData.renderFinishedSemaphore->getId(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, frameData.renderFinishedFence->getId());

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
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
			recreateSwapchain();
		}
		else if (result != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to present image.");
		}

		//Update frame counter
		currentFrame = (currentFrame + 1) % NUM_FRAMES_IN_FLIGHT;
	}

	void CoreContext::createCoreRessources(HWND windowHandle) {
		m_instance = new VK_Instance();
		m_instance->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_win32_surface" }));
		m_instance->addCheck(new VK_Check_Device_Extensions(false, { VK_EXT_DEBUG_UTILS_EXTENSION_NAME }));
		m_instance->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
		m_instance->create();
		//m_instance->printActiveExtensions();
		//m_instance->printActiveValidationLayers();

		m_surface = new VK_Surface(m_instance->getId(), windowHandle);
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

		m_swapchain = new VK_Swapchain(m_device, m_surface->getId(), VK_NULL_HANDLE);
		m_swapchain->create();
	}

	void CoreContext::createPerFrameRessources() {
		for (int i = 0; i < NUM_FRAMES_IN_FLIGHT; i++) {
			framesData[i].commandBuffer = m_device->getCommandBuffer(VK_Device::GRAPHICS);
			framesData[i].commandBuffer->create();
			m_device->debug_setName(VK_OBJECT_TYPE_COMMAND_BUFFER, (uint64_t)framesData[i].commandBuffer->getId(), "CommandBuffer frame");

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
	}

	void CoreContext::recreateSwapchain() {
		vkDeviceWaitIdle(m_device->getDevice());

		m_device->requerySurfaceData();

		//TODO: Update projection matrices

		delete m_managerFramebuffers->get("Main");

		VK_Swapchain* oldSwapchain = m_swapchain;
		VK_Swapchain* newSwapchain = new VK_Swapchain(m_device, m_surface->getId(), oldSwapchain->getId());
		newSwapchain->create();
		m_swapchain = newSwapchain;
		delete oldSwapchain;

		VK_Framebuffers* framebuffers = nullptr;
		framebuffers = new VK_Framebuffers(m_device, m_managerRenderpass->get("Main")->getId(), m_swapchain);
		framebuffers->create();
		m_managerFramebuffers->add("Main", framebuffers);

		for (int i = 0; i < NUM_FRAMES_IN_FLIGHT; i++) {
			framesData[i].commandBuffer->updateRenderArea();
		}
	}
}//end namespace