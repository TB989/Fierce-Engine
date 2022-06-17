#include "VK_Semaphore.h"

#include "VK_Device.h"

VK_Semaphore::VK_Semaphore(VK_Device* device) {
	m_device = device;

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreInfo.pNext = nullptr;
	semaphoreInfo.flags = 0;

	CHECK_VK(vkCreateSemaphore(m_device->getDevice(), &semaphoreInfo, nullptr, &semaphore), "Failed to create semaphore.");
}

VK_Semaphore::~VK_Semaphore() {
	vkDestroySemaphore(m_device->getDevice(), semaphore, nullptr);
}