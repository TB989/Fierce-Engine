#include "VK_DescriptorSetLayout.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	VK_DescriptorSetLayout::VK_DescriptorSetLayout(VkDevice device){
		m_device = device;

		m_createInfo = {};
		m_createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
	}

	VK_DescriptorSetLayout::~VK_DescriptorSetLayout(){
		vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
	}

	void VK_DescriptorSetLayout::create(){
		m_createInfo.bindingCount = static_cast<uint32_t>(m_bindings.size());
		m_createInfo.pBindings = m_bindings.data();

		if (vkCreateDescriptorSetLayout(m_device, &m_createInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create descriptor set layout.");
		}
	}

	void VK_DescriptorSetLayout::addBinding(uint32_t bind,VkDescriptorType type,uint32_t count,VkShaderStageFlags shaderStages){
		VkDescriptorSetLayoutBinding binding = {};
		binding.binding = bind;
		binding.descriptorType = type;
		binding.descriptorCount = count;
		binding.stageFlags = shaderStages;
		binding.pImmutableSamplers = nullptr;
		m_bindings.push_back(binding);
	}
}//end namespace