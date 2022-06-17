#include "VK_DescriptorSet.h"

#include "VK_Device.h"
#include "VK_DescriptorPool.h"
#include "VK_Pipeline.h"
#include "VK_Buffer.h"

VK_DescriptorSet::VK_DescriptorSet(VK_Device* device, VK_DescriptorPool* descriptorPool, VK_Pipeline* pipeline){
    m_device = device;
    m_descriptorPool = descriptorPool;

    VkDescriptorSetLayout layout = pipeline->getDescLayout();

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;
    allocInfo.descriptorPool = descriptorPool->getDescriptorPool();
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &layout;
    CHECK_VK(vkAllocateDescriptorSets(device->getDevice(), &allocInfo, &descriptorSet), "Failed to allocate descriptor sets.");
}

VK_DescriptorSet::~VK_DescriptorSet(){
    CHECK_VK(vkFreeDescriptorSets(m_device->getDevice(), m_descriptorPool->getDescriptorPool(), 1, &descriptorSet), "Failed to free descriptor sets.");
}

void VK_DescriptorSet::update(VK_Buffer* buffer){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = buffer->getBuffer();
    bufferInfo.offset = 0;
    bufferInfo.range = 2 * 16 * sizeof(float);

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.pNext = nullptr;
    descriptorWrite.dstSet = descriptorSet;
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;
    descriptorWrite.pImageInfo = nullptr;
    descriptorWrite.pTexelBufferView = nullptr;

    vkUpdateDescriptorSets(m_device->getDevice(), 1, &descriptorWrite, 0, nullptr);
}