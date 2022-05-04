#include "GL_Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

const std::string GL_Shader::SHADER_LIBRARY = "C:/Users/tmbal/Desktop/Fierce-Engine/OpenGLRenderer/res/";

GL_Shader::GL_Shader(std::string path) {
	type = getType(path);
	readSourceCode(path);
	createShader(path);
}

GL_Shader::~GL_Shader() {
	glDeleteShader(id);
	CHECK_GL(glGetError(), "Failed to delete shader.");
}

static inline bool endsWith(const std::string& s, const std::string& token) {
	return s.rfind(token) == (s.size() - token.size());
}

ShaderType GL_Shader::getType(std::string path) {
	if (endsWith(path, ".vert")) {
		return ShaderType::VERTEX_SHADER;
	}
	else if (endsWith(path, ".frag")) {
		return ShaderType::FRAGMENT_SHADER;
	}
	else {
		LOGGER->error("Shader %s is not a valid shader file.", path.c_str());
		return ShaderType::UNKNOWN;
	}
}

void GL_Shader::readSourceCode(std::string path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try{
		file.open(SHADER_LIBRARY + path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		sourceCode = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		LOGGER->error("Failed to read shader file %s.",path.c_str());
		LOGGER->error("%s",e.what());
	}
}

void GL_Shader::createShader(std::string path) {
	switch (type) {
	case VERTEX_SHADER:
		id = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT_SHADER:
		id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	CHECK_GL(glGetError(), "Failed to create shader.");

	//Load source code
	char const* source = sourceCode.c_str();
	glShaderSource(id, 1, &source, NULL);

	CHECK_GL(glGetError(), "Failed to load shader source.");

	//Compile shader
	glCompileShader(id);

	//Check compile
	GLint Result = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		LOGGER->error("Shader compilation failed for shader %s:\n%s\n", path.c_str(), &VertexShaderErrorMessage[0]);
		CHECK_GL(glGetError(), "Failed to compile shader.");
	}
}