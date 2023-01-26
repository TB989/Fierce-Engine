#pragma once

#include "src/Common.h"
#include "VulkanObject.h"

class VK_Device;

class VK_DescriptorPool : public VulkanObject{
public:
	VK_DescriptorPool(VK_Device* device);
	~VK_DescriptorPool();

	VkDescriptorPool getDescriptorPool() { return descriptorPool; }

private:
	VK_Device* m_device;

	VkDescriptorPool descriptorPool;
};