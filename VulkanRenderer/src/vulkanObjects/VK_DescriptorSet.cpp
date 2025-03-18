#include "VK_DescriptorSet.h"

#include "src/vulkanObjects/VK_Pipeline.h"
#include "src/vulkanObjects/VK_Buffer.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	Fierce::VK_DescriptorSet::VK_DescriptorSet(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorSetLayout descriptorLayout){
		m_device = device;
		m_descriptorPool = descriptorPool;

		m_layouts.push_back(descriptorLayout);

		m_allocateInfo = {};
		m_allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		m_allocateInfo.pNext = nullptr;
		m_allocateInfo.descriptorPool = descriptorPool;
		m_allocateInfo.descriptorSetCount = 1;
		m_allocateInfo.pSetLayouts = m_layouts.data();
	}

	VK_DescriptorSet::~VK_DescriptorSet(){
		vkFreeDescriptorSets(m_device,m_descriptorPool,1,&m_descriptorSet);
	}

	void VK_DescriptorSet::create(){
		if (vkAllocateDescriptorSets(m_device, &m_allocateInfo, &m_descriptorSet) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to allocate descriptor set.");
		}
	}
}//end namespace