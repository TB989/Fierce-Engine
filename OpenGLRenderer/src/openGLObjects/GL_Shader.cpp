#include "GL_Shader.h"

#include <fstream>

GL_Shader::GL_Shader(GLenum type) {
	id = glCreateShader(type);
	CHECK_GL(glGetError(), "Failed to create shader.");
}

GL_Shader::~GL_Shader() {
	glDeleteShader(id);
	CHECK_GL(glGetError(), "Failed to delete shader.");
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

void GL_Shader::addSourceCode(std::string filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		LOGGER->error("Failed to read shader: %s", filename);
	}

	std::string content;
	std::string line = "";
	while (!file.eof()) {
		std::getline(file, line);
		content.append(line + "\n");
	}

	file.close();

	const char* sourceCode = content.c_str();

	glShaderSource(id, 1, &sourceCode, NULL);
	CHECK_GL(glGetError(), "Failed to load shader source.");
}