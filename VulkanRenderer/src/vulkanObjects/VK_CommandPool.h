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

	public:
		void bindToGraphicsQueue() { m_bindToGraphicsQueue = true; }
		void bindToTransferQueue() { m_bindToGraphicsQueue = false; }

	private:
		//Create info
		VkCommandPoolCreateInfo m_createInfo={};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkCommandPool m_commandPool=VK_NULL_HANDLE;

		//Misc
		bool m_bindToGraphicsQueue=true;
	};
}//end namespace