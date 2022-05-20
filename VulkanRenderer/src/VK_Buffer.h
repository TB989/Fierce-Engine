#pragma once

#include "Common.h"

class VK_Device;

class VK_Buffer {
public:
	VK_Buffer(VK_Device* device, int size);
	~VK_Buffer();

	void loadData(int size, float* vertices);

	VkBuffer getBuffer() { return buffer; }

private:
	VK_Device* m_device;
	VkBuffer buffer;
	VkDeviceMemory memory;
};