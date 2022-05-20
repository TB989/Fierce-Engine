#include "VK_Buffer.h"

#include "VK_Device.h"

VK_Buffer::VK_Buffer(VK_Device* device, int size){
	m_device = device;

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.pNext = nullptr;
	bufferInfo.flags = 0;
	bufferInfo.size = size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	CHECK_VK(vkCreateBuffer(device->getDevice(), &bufferInfo, nullptr, &buffer),"Failed to create buffer.");

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device->getDevice(), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = m_device->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

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