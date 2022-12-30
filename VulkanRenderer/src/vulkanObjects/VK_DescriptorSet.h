#pragma once

#include "Common.h"
#include "VulkanObject.h"

class VK_Device;
class VK_DescriptorPool;
class VK_Pipeline;
class VK_Buffer;

class VK_DescriptorSet : public VulkanObject{
public:
	VK_DescriptorSet(VK_Device* device, VK_DescriptorPool* descriptorPool,VK_Pipeline* pipeline);
	~VK_DescriptorSet();

	VkDescriptorSet getDescriptorSet() { return descriptorSet; }

	void update(VK_Buffer* buffer);

private:
	VK_Device* m_device;
	VK_DescriptorPool* m_descriptorPool;

	VkDescriptorSet descriptorSet;
};