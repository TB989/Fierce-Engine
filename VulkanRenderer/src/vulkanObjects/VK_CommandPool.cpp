#include "VK_CommandPool.h"

#include "vulkanObjects/VK_Device.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce{

	VK_CommandPool::VK_CommandPool(VK_Device* device){
		m_device = device;

		m_createInfo={};
		m_createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		m_createInfo.queueFamilyIndex = m_device->getDeviceData()->graphicsQueueIndex;
	}

	VK_CommandPool::~VK_CommandPool(){
		vkDestroyCommandPool(m_device->getDevice(), m_commandPool, nullptr);
	}

	void VK_CommandPool::create(){
		if (vkCreateCommandPool(m_device->getDevice(), &m_createInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create command pool.");
		}
	}

}//end namespace