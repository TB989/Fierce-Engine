#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Sampler {
	public:
		VK_Sampler(VK_Device* device);
		~VK_Sampler();

		void create();
		VkSampler getId() { return m_sampler; }

	private:
		//Create info
		VkSamplerCreateInfo m_createInfo={};

		//Vulkan objects
		VK_Device* m_device = nullptr;
		VkSampler m_sampler = VK_NULL_HANDLE;
	};
}//end namespace