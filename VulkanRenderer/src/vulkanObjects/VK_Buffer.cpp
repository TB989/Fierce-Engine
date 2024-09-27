#include "VK_Buffer.h"

#include "vulkanObjects/VK_Device.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Buffer::VK_Buffer(VK_Device* device, int size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties){
		m_device = device;
		m_memoryFlags = properties;

		m_createInfo = {};
		m_createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.size = size;
		m_createInfo.usage = usage;

		m_allocateInfo = {};
		m_allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		m_allocateInfo.pNext = nullptr;
	}

	VK_Buffer::~VK_Buffer(){
		vkFreeMemory(m_device->getDevice(), m_memory, nullptr);
		vkDestroyBuffer(m_device->getDevice(), m_buffer, nullptr);
	}

	void VK_Buffer::create(){
		if (m_shareRessourcesWithTransferQueue) {
			m_createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			m_createInfo.queueFamilyIndexCount = 2;
			uint32_t indices[]= { m_device->getDeviceData()->graphicsQueueIndex,m_device->getDeviceData()->transferQueueIndex };
			m_createInfo.pQueueFamilyIndices = indices;
		}
		else {
			m_createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			m_createInfo.queueFamilyIndexCount = 0;
			m_createInfo.pQueueFamilyIndices = nullptr;
		}

		if (vkCreateBuffer(m_device->getDevice(), &m_createInfo, nullptr, &m_buffer) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create buffer.");
		}

		//Memory
		VkMemoryRequirements memRequirements = {};
		vkGetBufferMemoryRequirements(m_device->getDevice(), m_buffer, &memRequirements);
		m_allocateInfo.allocationSize = memRequirements.size;
		m_allocateInfo.memoryTypeIndex = m_device->findMemoryType(memRequirements.memoryTypeBits, m_memoryFlags);
		if (vkAllocateMemory(m_device->getDevice(), &m_allocateInfo, nullptr, &m_memory) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to allocate memory.");
		}

		if (vkBindBufferMemory(m_device->getDevice(), m_buffer, m_memory, 0) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to bind buffer memory.");
		}
	}

	void VK_Buffer::loadData(int size, float* vertices){
		void* data;
		if (vkMapMemory(m_device->getDevice(), m_memory, 0, size, 0, &data) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to map buffer memory.");
		}
		memcpy(data, vertices, (size_t)size);
		vkUnmapMemory(m_device->getDevice(), m_memory);
	}

	void VK_Buffer::loadData(int size, uint16_t* indices){
		void* data;
		if (vkMapMemory(m_device->getDevice(), m_memory, 0, size, 0, &data) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to map buffer memory.");
		}
		memcpy(data, indices, (size_t)size);
		vkUnmapMemory(m_device->getDevice(), m_memory);
	}

}//end namespace