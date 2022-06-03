#include "VK_Buffer.h"

#include "VK_Device.h"

VK_Buffer::VK_Buffer(VK_Device* device, int size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties){
	m_device = device;

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.pNext = nullptr;
	bufferInfo.flags = 0;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	CHECK_VK(vkCreateBuffer(device->getDevice(), &bufferInfo, nullptr, &buffer),"Failed to create buffer.");

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device->getDevice(), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = m_device->findMemoryType(memRequirements.memoryTypeBits, properties);

	CHECK_VK(vkAllocateMemory(m_device->getDevice(), &allocInfo, nullptr, &memory),"Failed to allocate buffer memory.");

	CHECK_VK(vkBindBufferMemory(m_device->getDevice(), buffer, memory, 0),"Failed to bind memory to buffer.");
}

VK_Buffer::~VK_Buffer(){
	vkDestroyBuffer(m_device->getDevice(), buffer, nullptr);
	vkFreeMemory(m_device->getDevice(), memory, nullptr);
}

void VK_Buffer::loadData(int size,float* vertices){
	void* data;
	vkMapMemory(m_device->getDevice(), memory, 0, size, 0, &data);
	memcpy(data, vertices, (size_t)size);
	vkUnmapMemory(m_device->getDevice(), memory);
}

void VK_Buffer::loadData(int size, uint16_t* indices) {
	void* data;
	vkMapMemory(m_device->getDevice(), memory, 0, size, 0, &data);
	memcpy(data, indices, (size_t)size);
	vkUnmapMemory(m_device->getDevice(), memory);
}

void VK_Buffer::loadData(float* mat1, float* mat2) {
	void* data1;
	vkMapMemory(m_device->getDevice(), memory, 0, 16*sizeof(float), 0, &data1);
	memcpy(data1, mat1, (size_t)(16*sizeof(float)));
	vkUnmapMemory(m_device->getDevice(), memory);

	void* data2;
	vkMapMemory(m_device->getDevice(), memory, 16*sizeof(float), 16 * sizeof(float), 0, &data2);
	memcpy(data2, mat2, (size_t)(16 * sizeof(float)));
	vkUnmapMemory(m_device->getDevice(), memory);
}