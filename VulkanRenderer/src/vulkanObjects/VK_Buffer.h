#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Buffer{
	public:
		VK_Buffer(VK_Device* device, int size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
		~VK_Buffer();

		void create();
		VkBuffer getId() { return m_buffer; }

	public:
		void shareRessourcesWithTransferQueue() { m_shareRessourcesWithTransferQueue = true; }

		void loadData(int size, float* vertices);
		void loadData(int size, uint16_t* indices);

	private:
		//Create info
		VkBufferCreateInfo m_createInfo={};
		VkMemoryAllocateInfo m_allocateInfo={};

		//Misc
		VkMemoryPropertyFlags m_memoryFlags = {};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkBuffer m_buffer=VK_NULL_HANDLE;
		VkDeviceMemory m_memory=VK_NULL_HANDLE;

		//Misc
		bool m_shareRessourcesWithTransferQueue = false;
	};

}//end namespace