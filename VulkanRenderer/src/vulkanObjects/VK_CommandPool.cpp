#include "VK_CommandPool.h"

#include "VK_Device.h"

VK_CommandPool::VK_CommandPool(VK_Device* device){
    m_device = device;

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.pNext = nullptr;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = device->getDeviceData()->graphicsQueueIndex;

    CHECK_VK(vkCreateCommandPool(device->getDevice(), &poolInfo, nullptr, &commandPool), "Failed to create command pool.");
}

VK_CommandPool::~VK_CommandPool(){
    vkDestroyCommandPool(m_device->getDevice(), commandPool, nullptr);
}