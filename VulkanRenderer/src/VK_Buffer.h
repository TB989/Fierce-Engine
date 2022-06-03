#pragma once

#include "Common.h"

class VK_Device;

class VK_Buffer {
public:
	VK_Buffer(VK_Device* device, int size,VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	~VK_Buffer();

	void loadData(int size, float* vertices);
	void loadData(int size, uint16_t* indices);
	void loadData(float* mat1, float* mat2);

	VkBuffer getBuffer() { return buffer; }

private:
	VK_Device* m_device;
	VkBuffer buffer;
	VkDeviceMemory memory;
};