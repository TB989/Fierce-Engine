#pragma once

#include "Common.h"
#include "VulkanObject.h"

#include "Renderer_API.h"

class VK_Device;

class VK_Shader :public VulkanObject{
public:
	VK_Shader(VK_Device* device, ShaderType shaderType);
	~VK_Shader();

	VkShaderModule getShader() { return shaderModule; }
	ShaderType getType() { return m_shaderType; }

	void addSourceCode(int sourceCodeSize, char* sourceCode);
	void create();

private:
	VkDevice m_device;

	ShaderType m_shaderType=ShaderType::UNKNOWN;
	VkShaderModuleCreateInfo createInfo = {};
	VkShaderModule shaderModule=VK_NULL_HANDLE;
};