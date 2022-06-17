#include "VK_Shader.h"

#include "VK_Device.h"

#include <fstream>

//const std::string VK_Shader::SHADER_LIBRARY = "C:/Users/tmbal/Desktop/Fierce-Engine/VulkanRenderer/res/";

VK_Shader::VK_Shader(VK_Device* device, ShaderType shaderType) {
	m_device = device->getDevice();
	m_shaderType = shaderType;

	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
}

VK_Shader::~VK_Shader() {
	vkDestroyShaderModule(m_device, shaderModule, nullptr);
}

void VK_Shader::create(){
	CHECK_VK(vkCreateShaderModule(m_device, &createInfo, nullptr, &shaderModule), "Failed to create shader module.");
}

void VK_Shader::setSourceCode(std::vector<char> sourceCode){
	createInfo.codeSize = sourceCode.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(sourceCode.data());
}

void VK_Shader::fillInShaderStageInfo(VkPipelineShaderStageCreateInfo createInfo) {
	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.pSpecializationInfo = nullptr;
	switch (m_shaderType) {
	case VERTEX_SHADER:
		createInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case FRAGMENT_SHADER:
		createInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	}
	createInfo.module = shaderModule;
	createInfo.pName = "main";
}

/**ShaderType VK_Shader::getType(std::string path) {
	if (contains(path, "vert")) {
		return ShaderType::VERTEX_SHADER;
	}
	else if (contains(path, "frag")) {
		return ShaderType::FRAGMENT_SHADER;
	}
	else{
		LOGGER->error("Shader %s is not a valid shader file.", path.c_str());
		return ShaderType::UNKNOWN;
	}
}*/

/**void VK_Shader::readSourceCode(std::string path) {
	std::ifstream stream(SHADER_LIBRARY + path, std::ios::ate | std::ios::binary);

	if (stream.is_open()) {
		size_t fileSize = (size_t)stream.tellg();
		sourceCode.resize(fileSize);
		stream.seekg(0);
		stream.read(sourceCode.data(), fileSize);
		stream.close();
	}
	else {
		LOGGER->error("Unable to read shader %s.", path.c_str());
	}
}*/