#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce {

	class VK_Pipeline;
	class VK_Buffer;

	class VK_DescriptorSet {
	public:
		VK_DescriptorSet(VkDevice device,VkDescriptorPool descriptorPool, VkDescriptorSetLayout descriptorLayout);
		~VK_DescriptorSet();

		void create();
		VkDescriptorSet getId() { return m_descriptorSet; }

	public:
		void update(VK_Buffer* buffer, uint32_t binding);
		void update(VK_Buffer* buffer);
		void update(VkImageView imageView, VkSampler imageSampler);
		void update(VK_Buffer* buffer, VkImageView imageView, VkSampler imageSampler);

	private:
		//Allocate info
		std::vector<VkDescriptorSetLayout> m_layouts;
		VkDescriptorSetAllocateInfo m_allocateInfo={};

		//Update info
		VkDescriptorImageInfo m_imageInfo={};
		VkDescriptorBufferInfo m_bufferInfo={};
		VkWriteDescriptorSet m_descriptorWrite={};

		//Vulkan objects
		VkDevice m_device = VK_NULL_HANDLE;
		VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;
		VkDescriptorSet m_descriptorSet = VK_NULL_HANDLE;
	};
}//end namespace