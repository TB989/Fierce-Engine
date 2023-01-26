#pragma once

#include "src/Common.h"
#include "VulkanObject.h"

class VK_Device;

class VK_Semaphore : public VulkanObject{
public:
	VK_Semaphore(VK_Device* device);
	~VK_Semaphore();

	VkSemaphore getSemaphore() { return semaphore; }

private:
	VK_Device* m_device;
	VkSemaphore semaphore;
};
