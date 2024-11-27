#pragma once

#include "vulkan/vulkan.h"

#include "src/FierceStrings.h"

#include <vector>

namespace Fierce {

	class VK_Device;

	class VK_Shader {
	public:
		VK_Shader(VK_Device* device);
		~VK_Shader();

		void create();
		VkShaderModule getId() { return m_shaderModule; }

		void setSourceCode(std::string name);

	private:
		//Create info
		VkShaderModuleCreateInfo m_createInfo = {};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkShaderModule m_shaderModule = VK_NULL_HANDLE;

		//Source code and shader library
		std::string shaderName;
		std::vector<char> m_sourceCode;
		const std::string SHADER_LIBRARY = "C:/Users/tmbal/Desktop/Fierce-Engine/Shaders/src/";
	};

}//end namespace