#include "VK_DescriptorPool.h"

#include "VK_Device.h"

VK_DescriptorPool::VK_DescriptorPool(VK_Device* device){
    m_device = device;

    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = 2;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.pNext = nullptr;
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = 2;

    CHECK_VK(vkCreateDescriptorPool(device->getDevice(), &poolInfo, nullptr, &descriptorPool), "Failed to create descriptor pool.");
}

VK_DescriptorPool::~VK_DescriptorPool(){
    vkDestroyDescriptorPool(m_device->getDevice(), descriptorPool, nullptr);
}