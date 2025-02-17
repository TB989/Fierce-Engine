#include "VK_Image.h"

#include "src/vulkanObjects/VK_Device.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	VK_Image::VK_Image(VK_Device* device, uint32_t width, uint32_t height,VkDeviceSize size, VkMemoryPropertyFlags properties,VkFormat format,VkImageUsageFlags usage){
		m_device = device;
		m_memoryFlags = properties;
		m_size = size;

		m_createInfo = {};
		m_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.imageType = VK_IMAGE_TYPE_2D;
		m_createInfo.format = format;
		m_createInfo.extent.width = static_cast<uint32_t>(width);
		m_createInfo.extent.height = static_cast<uint32_t>(height);
		m_createInfo.extent.depth = 1;
		m_createInfo.mipLevels = 1;
		m_createInfo.arrayLayers = 1;
		m_createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		m_createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		m_createInfo.usage = usage;
		m_createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		m_allocateInfo = {};
		m_allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		m_allocateInfo.pNext = nullptr;
	}

	VK_Image::~VK_Image(){
		vkFreeMemory(m_device->getDevice(), m_memory, nullptr);
		vkDestroyImage(m_device->getDevice(),m_image,nullptr);
	}

	void VK_Image::create(){
		if (m_shareRessourcesWithTransferQueue) {
			m_createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			m_createInfo.queueFamilyIndexCount = 2;
			uint32_t indices[] = { m_device->getDeviceData()->graphicsQueueIndex,m_device->getDeviceData()->transferQueueIndex };
			m_createInfo.pQueueFamilyIndices = indices;
		}
		else {
			m_createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			m_createInfo.queueFamilyIndexCount = 0;
			m_createInfo.pQueueFamilyIndices = nullptr;
		}

		if (vkCreateImage(m_device->getDevice(), &m_createInfo, nullptr, &m_image) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create image.");
		}

		//Memory
		VkMemoryRequirements memRequirements = {};
		vkGetImageMemoryRequirements(m_device->getDevice(), m_image, &memRequirements);
		m_allocateInfo.allocationSize = memRequirements.size;
		m_allocateInfo.memoryTypeIndex = m_device->findMemoryType(memRequirements.memoryTypeBits, m_memoryFlags);
		if (vkAllocateMemory(m_device->getDevice(), &m_allocateInfo, nullptr, &m_memory) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to allocate memory.");
		}

		if (vkBindImageMemory(m_device->getDevice(), m_image, m_memory, 0) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to bind image memory.");
		}
	}
}//end namespace