#include "VK_Semaphore.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Semaphore::VK_Semaphore(VkDevice device){
		m_device = device;

		m_createInfo={};
		m_createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
	}

	VK_Semaphore::~VK_Semaphore(){
		vkDestroySemaphore(m_device, m_semaphore, nullptr);
	}

	void VK_Semaphore::create(){
		if (vkCreateSemaphore(m_device, &m_createInfo, nullptr, &m_semaphore) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create semaphore.");
		}
	}

}//end namespace