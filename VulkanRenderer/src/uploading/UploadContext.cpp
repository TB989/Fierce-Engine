#include "UploadContext.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_CommandBuffer.h"
#include "vulkanObjects/VK_Buffer.h"
#include "vulkanObjects/VK_Image.h"

#include "assets/VK_Mesh.h"
#include "assets/VK_Texture.h"

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

	void UploadContext::copyMesh(VK_Mesh* mesh){
		VK_Buffer* vertexBuffer=new VK_Buffer(m_device, mesh->getNumVertices() * sizeof(float), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		vertexBuffer->shareRessourcesWithTransferQueue();
		vertexBuffer->create();

		VK_Buffer* indexBuffer= new VK_Buffer(m_device, mesh->getNumIndices() * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		indexBuffer->shareRessourcesWithTransferQueue();
		indexBuffer->create();

		copyBuffer(mesh->getVertexBuffer(), vertexBuffer, mesh->getNumVertices() * sizeof(float));
		copyBuffer(mesh->getIndexBuffer(), indexBuffer, mesh->getNumIndices() * sizeof(uint16_t));

		mesh->swapBuffers(vertexBuffer,indexBuffer);

		m_buffersToDelete.push_back(vertexBuffer);
		m_buffersToDelete.push_back(indexBuffer);
	}

	void UploadContext::copyTexture(VK_Texture* texture){
		VK_Buffer* buffer = nullptr;
		VK_Image* image= new VK_Image(m_device, texture->getWidth(), texture->getHeight(), texture->getSize(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		image->shareRessourcesWithTransferQueue();
		image->create();

		m_transferCommandBuffer->imageBarrier(image->getId(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		m_transferCommandBuffer->copy(texture->getBuffer()->getId(), image->getId(), texture->getWidth(), texture->getHeight());

		if (m_device->hasDedicatedTransferQueue()) {
			m_graphicsCommandBuffer->imageBarrier(image->getId(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}
		else {
			m_transferCommandBuffer->imageBarrier(image->getId(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}

		texture->swapBuffers(buffer,image);

		m_buffersToDelete.push_back(buffer);
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

		for (VK_Buffer* buffer:m_buffersToDelete) {
			delete buffer;
		}
	}

}//end namespace