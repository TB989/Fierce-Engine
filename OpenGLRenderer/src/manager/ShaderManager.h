#pragma once

#include "Common.h"

#include "openGLObjects/GL_Shader.h"

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();

	GL_Shader* getShader(ShaderID id) { return ID_Shader_map[id]; }

	ShaderID addShader(ShaderType shaderType, int sourceCodeSize, char* sourceCode);

private:

	uint32_t counter = 0;
	std::unordered_map<uint32_t, GL_Shader*> ID_Shader_map;

};