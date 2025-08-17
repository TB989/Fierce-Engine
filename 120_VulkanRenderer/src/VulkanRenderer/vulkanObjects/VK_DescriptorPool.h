#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce {
	class VK_DescriptorPool {
	public:
		VK_DescriptorPool(VkDevice device);
		~VK_DescriptorPool();

		void create();
		VkDescriptorPool getId() { return m_descriptorPool; }

	public:
		void addDescriptorType(VkDescriptorType type,int numberDescriptors);

	private:
		//Create info
		std::vector<VkDescriptorPoolSize> m_poolSizes;
		VkDescriptorPoolCreateInfo m_createInfo={};

		//Vulkan objects
		VkDevice m_device = VK_NULL_HANDLE;
		VkDescriptorPool m_descriptorPool=VK_NULL_HANDLE;
	};
}//end namespace