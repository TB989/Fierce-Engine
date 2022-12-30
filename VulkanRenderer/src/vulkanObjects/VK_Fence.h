#pragma once

#include "Common.h"
#include "VulkanObject.h"

class VK_Device;

class VK_Fence : public VulkanObject{
public:
	VK_Fence(VK_Device* device);
	~VK_Fence();

	VkFence getFence() { return fence; }

private:
	VK_Device* m_device;
	VkFence fence;
};