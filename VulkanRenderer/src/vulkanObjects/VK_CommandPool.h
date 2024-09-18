#pragma once

#include "vulkan/vulkan.h"

namespace Fierce{

	class VK_Device;

	class VK_CommandPool {
	public:
		VK_CommandPool(VK_Device* device);
		~VK_CommandPool();

		void create();
		VkCommandPool getId() { return m_commandPool; }

	private:
		//Create info
		VkCommandPoolCreateInfo m_createInfo={};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkCommandPool m_commandPool=VK_NULL_HANDLE;

	};
}//end namespace