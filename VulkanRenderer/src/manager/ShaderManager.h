#pragma once

#include "Common.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Shader.h"

class ShaderManager {
public:
	ShaderManager(VK_Device* device);
	~ShaderManager();

	uint32_t addShader(ShaderType shaderType);

private:
	void createAllShaders();
	void deleteAllShaders();

private:
	VK_Device* m_device;

	uint32_t counter = 0;
	std::unordered_map<uint32_t,VK_Shader*> shaders;
};