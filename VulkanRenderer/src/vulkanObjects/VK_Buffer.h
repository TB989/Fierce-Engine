#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Buffer{
	public:
		VK_Buffer(VK_Device* device, int size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
		virtual ~VK_Buffer();

		void create();
		VkBuffer getId() { return m_buffer; }

	public:
		void shareRessourcesWithTransferQueue() { m_shareRessourcesWithTransferQueue = true; }
		void setKeepMapped(bool keepMapped) { m_keepMapped = keepMapped; }

		VkDeviceSize getSize() { return m_size; }

		void loadData(int size, float* vertices);
		void loadData(int size, uint16_t* indices);
		void loadData(int size, int index,float* matrix);
		void loadData(int size, float* view, float* proj);
		void loadData(int size, float* model, float* view, float* proj);
		void loadData(int size, unsigned char* data);

	protected:
		VK_Device* m_device = nullptr;

	private:
		//Create info
		VkBufferCreateInfo m_createInfo={};
		VkMemoryAllocateInfo m_allocateInfo={};

		//Misc
		VkMemoryPropertyFlags m_memoryFlags = {};
		VkDeviceSize m_size=0;

		//Vulkan objects
		VkBuffer m_buffer=VK_NULL_HANDLE;
		VkDeviceMemory m_memory=VK_NULL_HANDLE;

		//Misc
		bool m_shareRessourcesWithTransferQueue = false;
		bool m_keepMapped=false;
		void* m_mappedRegion;
	};

}//end namespace