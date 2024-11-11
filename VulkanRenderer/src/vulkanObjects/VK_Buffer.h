#pragma once

#include "vulkan/vulkan.h"

#include "glm.hpp"

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

		VkDeviceSize getSize() { return m_size; }

		void loadData(int size, float* vertices);
		void loadData(int size, uint16_t* indices);
		void loadData(int size, glm::mat4 model, glm::mat4 view, glm::mat4 proj);
		void loadData(int size, float* view, float* proj);
		void loadData(int size, float* model, float* view, float* proj);
		void loadData(int size, unsigned char* data);

	private:
		//Create info
		VkBufferCreateInfo m_createInfo={};
		VkMemoryAllocateInfo m_allocateInfo={};

		//Misc
		VkMemoryPropertyFlags m_memoryFlags = {};
		VkDeviceSize m_size=0;

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkBuffer m_buffer=VK_NULL_HANDLE;
		VkDeviceMemory m_memory=VK_NULL_HANDLE;

		//Misc
		bool m_shareRessourcesWithTransferQueue = false;
	};

}//end namespace