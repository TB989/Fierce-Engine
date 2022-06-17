#include "GL_Shader.h"

GL_Shader::GL_Shader(ShaderType shaderType) {
	m_shaderType = shaderType;
	switch (shaderType) {
	case ShaderType::VERTEX_SHADER:
		id = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::FRAGMENT_SHADER:
		id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	CHECK_GL(glGetError(), "Failed to create shader.");
}

GL_Shader::~GL_Shader() {
	glDeleteShader(id);
	CHECK_GL(glGetError(), "Failed to delete shader.");
}

void GL_Shader::addSourceCode(int sourceCodeSize, char* sourceCode){
	glShaderSource(id, 1, &sourceCode, &sourceCodeSize);
	CHECK_GL(glGetError(), "Failed to load shader source.");
}

void GL_Shader::create() {
	glCompileShader(id);

	GLint Result = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		LOGGER->error("Shader compilation failed for shader:\n%s\n",&VertexShaderErrorMessage[0]);
		CHECK_GL(glGetError(), "Failed to compile shader.");
	}
}