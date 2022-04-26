#pragma once

#include "Common.h"
#include "GL_Include.h"

#include "GL_ShaderType.h"

class GL_Shader {
public:
	GL_Shader(std::string path);
	~GL_Shader();

	GLuint getId() { return id; };
private:
	ShaderType getType(std::string path);
	void readSourceCode(std::string path);
	void createShader(std::string path);

private:
	static const std::string SHADER_LIBRARY;

	ShaderType type;
	std::string sourceCode;
	GLuint id = -1;
};