#include "VK_UBO.h"

#include "src/vulkanObjects/VK_Device.h"
#include "src/vulkanObjects/VK_DescriptorPool.h"

namespace Fierce {
	VK_UBO::VK_UBO(VK_Device* device, int size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) :VK_Buffer(device, size, usage, properties) {
		setKeepMapped(true);
	}

	VK_UBO::~VK_UBO() {
		delete m_descriptorSet;
	}

	void VK_UBO::createDescriptorSet(VK_DescriptorPool* descriptorPool, VkDescriptorSetLayout descriptorSetLayout) {
		m_descriptorSet = new VK_DescriptorSet(m_device->getDevice(), descriptorPool->getId(), descriptorSetLayout);
		m_descriptorSet->create();
	}

	void VK_UBO::update(VK_Buffer* buffer, uint32_t binding) {
		m_descriptorSet->update(buffer, binding);
	}

	void VK_UBO::update(VK_Buffer* buffer) {
		m_descriptorSet->update(buffer);
	}

	void VK_UBO::update(VkImageView imageView, VkSampler imageSampler) {
		m_descriptorSet->update(imageView, imageSampler);
	}

	void VK_UBO::update(VK_Buffer* buffer, VkImageView imageView, VkSampler imageSampler) {
		m_descriptorSet->update(buffer, imageView, imageSampler);
	}
}//end namespace