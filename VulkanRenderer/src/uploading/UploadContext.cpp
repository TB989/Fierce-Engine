#include "UploadContext.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_CommandBuffer.h"
#include "vulkanObjects/VK_Buffer.h"
#include "vulkanObjects/VK_Image.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

	UploadContext::UploadContext(VK_Device* device){
		m_device = device;

		m_transferCommandBuffer = m_device->getCommandBuffer(VK_Device::TRANSFER);
		m_graphicsCommandBuffer = m_device->getCommandBuffer(VK_Device::GRAPHICS);

		m_transferCommandBuffer->startRecording();
		m_graphicsCommandBuffer->startRecording();
	}

	UploadContext::~UploadContext(){
		m_device->releaseCommandBuffer(m_transferCommandBuffer);
		m_device->releaseCommandBuffer(m_graphicsCommandBuffer);
	}

	void UploadContext::copyBuffer(VK_Buffer* source, VK_Buffer* destination, VkDeviceSize size){
		m_transferCommandBuffer->copy(source->getId(),destination->getId(),size);
	}

	void UploadContext::copyImage(VK_Buffer* source, VK_Image* destination, uint32_t width, uint32_t height){
		m_transferCommandBuffer->imageBarrier(destination->getId(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		m_transferCommandBuffer->copy(source->getId(),destination->getId(),width,height);

		if (m_device->hasDedicatedTransferQueue()) {
			m_graphicsCommandBuffer->imageBarrier(destination->getId(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}
		else {
			m_transferCommandBuffer->imageBarrier(destination->getId(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}
	}

	void UploadContext::startAndWaitForUpload(){
		m_transferCommandBuffer->endRecording();
		m_graphicsCommandBuffer->endRecording();

		m_device->submitCommandBuffer(VK_Device::QUEUE_TYPE::TRANSFER, m_transferCommandBuffer->getId(), VK_NULL_HANDLE, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);
		if (vkQueueWaitIdle(m_device->getTransferQueue()) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to wait for idle queue.");
		}

		if (m_device->hasDedicatedTransferQueue()) {
			m_device->submitCommandBuffer(VK_Device::QUEUE_TYPE::GRAPHICS, m_graphicsCommandBuffer->getId(), VK_NULL_HANDLE, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);
			if (vkQueueWaitIdle(m_device->getGraphicsQueue()) != VK_SUCCESS) {
				RenderSystem::LOGGER->error("Failed to wait for idle queue.");
			}
		}
	}

}//end namespace