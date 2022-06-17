#pragma once

#include "Renderer_API.h"

#include "Common.h"
#include "GL_Include.h"

class GL_Shader {
public:
	GL_Shader(ShaderType shaderType);
	~GL_Shader();

	GLuint getId() { return id; }
	ShaderType getType() { return m_shaderType; }

	void addSourceCode(int sourceCodeSize, char* sourceCode);
	void create();

private:
	ShaderType m_shaderType;
	GLuint id = -1;
};