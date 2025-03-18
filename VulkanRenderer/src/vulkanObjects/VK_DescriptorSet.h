#pragma once

#include "vulkan/vulkan.h"

#include "src/vulkanObjects/VK_Buffer.h"

#include <vector>

namespace Fierce {

	class VK_Pipeline;

	class VK_DescriptorSet {
	public:
		VK_DescriptorSet(VkDevice device,VkDescriptorPool descriptorPool, VkDescriptorSetLayout descriptorLayout);
		~VK_DescriptorSet();

		void create();
		VkDescriptorSet getId() { return m_descriptorSet; }

	public:
		inline void update(VK_Buffer* buffer, uint32_t binding) {
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

		inline void update(VK_Buffer* buffer) {
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

		inline void update(VkImageView imageView, VkSampler imageSampler) {
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

		inline void update(VK_Buffer* buffer, VkImageView imageView, VkSampler imageSampler) {
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