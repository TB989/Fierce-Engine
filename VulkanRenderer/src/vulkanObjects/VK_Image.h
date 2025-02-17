#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Image {
	public:
		VK_Image(VK_Device* device,uint32_t width,uint32_t height, VkDeviceSize size, VkMemoryPropertyFlags properties, VkFormat format, VkImageUsageFlags usage);
		~VK_Image();

		void create();
		VkImage getId() { return m_image; }

	public:
		void shareRessourcesWithTransferQueue() { m_shareRessourcesWithTransferQueue = true; }

		VkDeviceSize getSize() { return m_size; }

	private:
		//Create info
		VkImageCreateInfo m_createInfo={};
		VkMemoryAllocateInfo m_allocateInfo = {};

		//Misc
		VkMemoryPropertyFlags m_memoryFlags = {};
		VkDeviceSize m_size = 0;

		//Vulkan objects
		VK_Device* m_device = nullptr;
		VkImage m_image=VK_NULL_HANDLE;
		VkDeviceMemory m_memory=VK_NULL_HANDLE;

		//Misc
		bool m_shareRessourcesWithTransferQueue = false;
	};
}//end namespace