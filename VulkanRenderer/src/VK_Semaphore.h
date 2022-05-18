#pragma once

#include "Common.h"

class VK_Device;

class VK_Semaphore {
public:
	VK_Semaphore(VK_Device* device);
	~VK_Semaphore();

	VkSemaphore getSemaphore() { return semaphore; }

private:
	VK_Device* m_device;
	VkSemaphore semaphore;
};
