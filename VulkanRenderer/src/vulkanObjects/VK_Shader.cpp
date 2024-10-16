#include "VK_Shader.h"

#include "renderSystem/RenderSystem.h"

#include <fstream>

namespace Fierce {

	VK_Shader::VK_Shader(VkDevice device){
		m_device = device;

		m_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
	}

	VK_Shader::~VK_Shader(){
		vkDestroyShaderModule(m_device, m_shaderModule, nullptr);
	}

	void VK_Shader::create(){
		if (vkCreateShaderModule(m_device, &m_createInfo, nullptr, &m_shaderModule)!=VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create shader module.");
		}
	}

	void VK_Shader::setSourceCode(std::string name) {
		std::string path = SHADER_LIBRARY;
		path.append(name);
		std::ifstream stream(path, std::ios::ate | std::ios::binary);

		if (stream.is_open()) {
			size_t fileSize = (size_t)stream.tellg();
			m_sourceCode.resize(fileSize);
			stream.seekg(0);
			stream.read(m_sourceCode.data(), fileSize);
			stream.close();
		}
		else {
			RenderSystem::LOGGER->error("Unable to read shader %s.", name.c_str());
		}

		m_createInfo.codeSize = m_sourceCode.size();
		m_createInfo.pCode = reinterpret_cast<const uint32_t*>(m_sourceCode.data());
	}

}//end namespace