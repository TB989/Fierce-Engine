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

	void VK_DescriptorSet::update(VK_Buffer* buffer, uint32_t binding){
		m_bufferInfo = {};
		m_bufferInfo.buffer = buffer->getId();
		m_bufferInfo.offset = 0;
		m_bufferInfo.range = buffer->getSize();

		m_descriptorWrite = {};
		m_descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		m_descriptorWrite.pNext = nullptr;
		m_descriptorWrite.dstSet = m_descriptorSet;
		m_descriptorWrite.dstBinding = binding;
		m_descriptorWrite.dstArrayElement = 0;
		m_descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		m_descriptorWrite.descriptorCount = 1;
		m_descriptorWrite.pBufferInfo = &m_bufferInfo;
		m_descriptorWrite.pImageInfo = nullptr;
		m_descriptorWrite.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(m_device, 1, &m_descriptorWrite, 0, nullptr);
	}

	void VK_DescriptorSet::update(VK_Buffer* buffer) {
		m_bufferInfo = {};
		m_bufferInfo.buffer = buffer->getId();
		m_bufferInfo.offset = 0;
		m_bufferInfo.range = buffer->getSize();

		m_descriptorWrite = {};
		m_descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		m_descriptorWrite.pNext = nullptr;
		m_descriptorWrite.dstSet = m_descriptorSet;
		m_descriptorWrite.dstBinding = 0;
		m_descriptorWrite.dstArrayElement = 0;
		m_descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		m_descriptorWrite.descriptorCount = 1;
		m_descriptorWrite.pBufferInfo = &m_bufferInfo;
		m_descriptorWrite.pImageInfo = nullptr;
		m_descriptorWrite.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(m_device, 1, &m_descriptorWrite, 0, nullptr);
	}

	void VK_DescriptorSet::update(VkImageView imageView, VkSampler imageSampler) {
		m_imageInfo = {};
		m_imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		m_imageInfo.imageView = imageView;
		m_imageInfo.sampler = imageSampler;

		VkWriteDescriptorSet m_descriptorWrite = {};
		m_descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		m_descriptorWrite.pNext = nullptr;
		m_descriptorWrite.dstSet = m_descriptorSet;
		m_descriptorWrite.dstBinding = 0;
		m_descriptorWrite.dstArrayElement = 0;
		m_descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		m_descriptorWrite.descriptorCount = 1;
		m_descriptorWrite.pBufferInfo = nullptr;
		m_descriptorWrite.pImageInfo = &m_imageInfo;
		m_descriptorWrite.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(m_device, 1, &m_descriptorWrite, 0, nullptr);
	}

	void VK_DescriptorSet::update(VK_Buffer* buffer, VkImageView imageView, VkSampler imageSampler){
		m_bufferInfo = {};
		m_bufferInfo.buffer = buffer->getId();
		m_bufferInfo.offset = 0;
		m_bufferInfo.range = buffer->getSize();

		m_imageInfo = {};
		m_imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		m_imageInfo.imageView = imageView;
		m_imageInfo.sampler = imageSampler;

		std::vector<VkWriteDescriptorSet> writes;
		VkWriteDescriptorSet m_descriptorWrite1 = {};
		m_descriptorWrite1.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		m_descriptorWrite1.pNext = nullptr;
		m_descriptorWrite1.dstSet = m_descriptorSet;
		m_descriptorWrite1.dstBinding = 0;
		m_descriptorWrite1.dstArrayElement = 0;
		m_descriptorWrite1.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		m_descriptorWrite1.descriptorCount = 1;
		m_descriptorWrite1.pBufferInfo = &m_bufferInfo;
		m_descriptorWrite1.pImageInfo = nullptr;
		m_descriptorWrite1.pTexelBufferView = nullptr;
		writes.push_back(m_descriptorWrite1);

		VkWriteDescriptorSet m_descriptorWrite2 = {};
		m_descriptorWrite2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		m_descriptorWrite2.pNext = nullptr;
		m_descriptorWrite2.dstSet = m_descriptorSet;
		m_descriptorWrite2.dstBinding = 1;
		m_descriptorWrite2.dstArrayElement = 0;
		m_descriptorWrite2.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		m_descriptorWrite2.descriptorCount = 1;
		m_descriptorWrite2.pBufferInfo = nullptr;
		m_descriptorWrite2.pImageInfo = &m_imageInfo;
		m_descriptorWrite2.pTexelBufferView = nullptr;
		writes.push_back(m_descriptorWrite2);

		vkUpdateDescriptorSets(m_device, 2, writes.data(), 0, nullptr);
	}
}//end namespace