#include "VK_Fence.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Fence::VK_Fence(VkDevice device){
		m_device = device;

		m_createInfo={};
		m_createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	}

	VK_Fence::~VK_Fence(){
		vkDestroyFence(m_device, m_fence, nullptr);
	}

	void VK_Fence::create(){
		if (vkCreateFence(m_device, &m_createInfo, nullptr, &m_fence) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create fence.");
		}
	}

}//end namespace