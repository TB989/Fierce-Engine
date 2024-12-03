#include "VK_DescriptorPool.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	VK_DescriptorPool::VK_DescriptorPool(VkDevice device){
		m_device = device;

		m_createInfo = {};
		m_createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	}

	VK_DescriptorPool::~VK_DescriptorPool(){
		vkDestroyDescriptorPool(m_device,m_descriptorPool,nullptr);
	}

	void VK_DescriptorPool::create(){
		m_createInfo.poolSizeCount = static_cast<uint32_t>(m_poolSizes.size());
		m_createInfo.pPoolSizes = m_poolSizes.data();

		if (vkCreateDescriptorPool(m_device, &m_createInfo, nullptr, &m_descriptorPool) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create descriptor pool.");
		}
	}

	void VK_DescriptorPool::addDescriptorType(VkDescriptorType type, int numberDescriptors){
		VkDescriptorPoolSize m_poolSize = {};
		m_poolSize.type = type;
		m_poolSize.descriptorCount = numberDescriptors;
		m_poolSizes.push_back(m_poolSize);

		m_createInfo.maxSets = static_cast<uint32_t>(numberDescriptors);
	}
}//end namespace