#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce{
	class VK_DescriptorSetLayout {
	public:
		VK_DescriptorSetLayout(VkDevice device);
		~VK_DescriptorSetLayout();

		void create();
		VkDescriptorSetLayout getId() { return m_descriptorSetLayout; }

		void addBinding(uint32_t bind, VkDescriptorType type, uint32_t count, VkShaderStageFlags shaderStages);

	private:
		//Create info
		VkDescriptorSetLayoutCreateInfo m_createInfo = {};

		//Bindings
		std::vector<VkDescriptorSetLayoutBinding> m_bindings;

		//Vulkan objects
		VkDevice m_device = VK_NULL_HANDLE;
		VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
	};
}//end namespace