#pragma once

#include "vulkan/vulkan.h"

#include "src/utils/FierceStrings.h"
#include "src/include/FileSystem.h"

#include <vector>

namespace Fierce {

	class VK_Device;

	class VK_Shader {
	public:
		VK_Shader(VK_Device* device,BinaryFileReader* reader);
		~VK_Shader();

		void create();
		VkShaderModule getId() { return m_shaderModule; }

		void setSourceCode(std::string name);

	private:
		BinaryFileReader* m_reader = nullptr;

		//Create info
		VkShaderModuleCreateInfo m_createInfo = {};

		//Vulkan objects
		VK_Device* m_device=nullptr;
		VkShaderModule m_shaderModule = VK_NULL_HANDLE;

		//Source code and shader library
		std::string shaderName;
		char* m_sourceCode=nullptr;
	};

}//end namespace