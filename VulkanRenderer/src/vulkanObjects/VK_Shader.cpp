#include "VK_Shader.h"

#include "VK_Device.h"

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

void VK_Shader::addSourceCode(int sourceCodeSize, char* sourceCode) {
	createInfo.codeSize = sourceCodeSize;
	createInfo.pCode = reinterpret_cast<const uint32_t*>(sourceCode);
}