#pragma once

#include "Common.h"

class VK_Device;

enum ShaderType {
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	UNKNOWN
};

class VK_Shader {
public:
	VK_Shader(VK_Device* device, std::string path);
	~VK_Shader();

	VkShaderModule getId() { return shaderModule; }
	void fillInShaderStageInfo(VkPipelineShaderStageCreateInfo createInfo);

private:
	ShaderType getType(std::string path);
	void readSourceCode(std::string path);
	void createShader(std::string path);

	static inline bool contains(const std::string& s, const std::string& token) {
		return s.find(token) != std::string::npos;
	}

private:
	static const std::string SHADER_LIBRARY;

	VkDevice m_device;

	ShaderType type;
	std::vector<char> sourceCode;
	VkShaderModule shaderModule;
};