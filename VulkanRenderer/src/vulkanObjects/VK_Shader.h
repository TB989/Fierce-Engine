#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Shader {
	public:
		VK_Shader(VK_Device* device);
		~VK_Shader();

		void create();
		VkShaderModule getId() { return m_shaderModule; }

		void setSourceCode(size_t size, char* sourceCode);

	private:
		//Create info
		VkShaderModuleCreateInfo m_createInfo = {};

		//Vulkan objects
		VK_Device* m_device = nullptr;
		VkShaderModule m_shaderModule = VK_NULL_HANDLE;
	};

}//end namespace