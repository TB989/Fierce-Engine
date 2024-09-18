#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Semaphore {
	public:
		VK_Semaphore(VkDevice device);
		~VK_Semaphore();

		void create();
		VkSemaphore getId() { return m_semaphore; }

	private:
		//Create info
		VkSemaphoreCreateInfo m_createInfo={};

		//Vulkan objects
		VkDevice m_device=VK_NULL_HANDLE;
		VkSemaphore m_semaphore=VK_NULL_HANDLE;
	};

}//end namespace