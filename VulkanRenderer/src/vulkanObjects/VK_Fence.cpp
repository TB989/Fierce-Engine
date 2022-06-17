#include "VK_Fence.h"

#include "VK_Device.h"

VK_Fence::VK_Fence(VK_Device* device) {
	m_device = device;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.pNext = nullptr;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	CHECK_VK(vkCreateFence(m_device->getDevice(), &fenceInfo, nullptr, &fence), "Failed to create fence.");
}

VK_Fence::~VK_Fence() {
	vkDestroyFence(m_device->getDevice(), fence, nullptr);
}