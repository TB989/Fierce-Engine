#pragma once

#include "src/Common.h"
#include "VulkanObject.h"

#include "RendererBase.h"

class VK_Device;

class VK_Shader :public VulkanObject{
public:
	VK_Shader(VK_Device* device);
	~VK_Shader();

	VkShaderModule getShader() { return shaderModule; }

	void addSourceCode(int sourceCodeSize, char* sourceCode);
	void create();

private:
	VkDevice m_device;

	VkShaderModuleCreateInfo createInfo = {};
	VkShaderModule shaderModule=VK_NULL_HANDLE;
};