#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Fence {
	public:
		VK_Fence(VkDevice device);
		~VK_Fence();

		void create();
		VkFence getId() { return m_fence; }

	private:
		//Create info
		VkFenceCreateInfo m_createInfo={};

		//Vulkan objects
		VkDevice m_device=VK_NULL_HANDLE;
		VkFence m_fence=VK_NULL_HANDLE;
	};

}//end namespace