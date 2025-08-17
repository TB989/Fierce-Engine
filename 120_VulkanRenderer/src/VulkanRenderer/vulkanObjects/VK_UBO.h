#pragma once

#include "vulkan/vulkan.h"

#include "src/VulkanRenderer/vulkanObjects/VK_Buffer.h"
#include "src/VulkanRenderer/vulkanObjects/VK_DescriptorSet.h"

namespace Fierce {

	class VK_Device;
	class VK_DescriptorPool;

	class VK_UBO :public VK_Buffer {
	public:
		VK_UBO(VK_Device* device, int size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
		~VK_UBO();

		void createDescriptorSet(VK_DescriptorPool* descriptorPool, VkDescriptorSetLayout descriptorSetLayout);

		VkDescriptorSet getDescriptorSet() { return m_descriptorSet->getId(); }

	public:
		void update(VK_Buffer* buffer, uint32_t binding);
		void update(VK_Buffer* buffer);
		void update(VkImageView imageView, VkSampler imageSampler);
		void update(VK_Buffer* buffer, VkImageView imageView, VkSampler imageSampler);

	private:
		VK_DescriptorSet* m_descriptorSet = nullptr;
	};
}//end namespace