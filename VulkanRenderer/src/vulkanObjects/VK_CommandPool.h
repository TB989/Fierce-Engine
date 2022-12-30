#pragma once

#include "Common.h"
#include "VulkanObject.h"

class VK_Device;

class VK_CommandPool : public VulkanObject{
public:
	VK_CommandPool(VK_Device* device);
	~VK_CommandPool();

	VkCommandPool getCommandPool() { return commandPool; }

private:
	VK_Device* m_device;
	VkCommandPool commandPool;
};