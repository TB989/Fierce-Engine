#include "GL_Pipeline.h"

GL_Pipeline::GL_Pipeline(GL_Shader* shader1, GL_Shader* shader2) {
	id = glCreateProgram();
	CHECK_GL(glGetError(),"Failed to create shader proram.");

	//Attach shaders
	shaderList.push_back(shader1);
	glAttachShader(id, shader1->getId());
	CHECK_GL(glGetError(), "Failed to attach shader.");
	shaderList.push_back(shader2);
	glAttachShader(id, shader2->getId());
	CHECK_GL(glGetError(), "Failed to create shader.");
}

GL_Pipeline::~GL_Pipeline() {
	glUseProgram(0);
	CHECK_GL(glGetError(), "Failed to use program.");
	for (int i = 0; i < shaderList.size(); i++) {
		glDetachShader(id, shaderList[i]->getId());
		CHECK_GL(glGetError(), "Failed to detach shader.");
	}
	glDeleteProgram(id);
	CHECK_GL(glGetError(), "Failed to delete program.");
}

void GL_Pipeline::create() {
	//Set vertex attributes
	for (VertexInput* input:vertexInputs) {
		glBindAttribLocation(id, input->location, input->name.c_str());
		CHECK_GL(glGetError(), "Failed to bind attribute location.");
	}

	//Link program
	glLinkProgram(id);

	GLint Result = GL_FALSE;

	//Check linking
	glGetProgramiv(id, GL_LINK_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		LOGGER->error("Shader program linking failed for program:\n%s\n", &ProgramErrorMessage[0]);
		CHECK_GL(glGetError(), "Failed to link program.");
	}

	//Validate program
	glValidateProgram(id);

	//Check validation
	glGetProgramiv(id, GL_VALIDATE_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		LOGGER->error("Shader program validation failed for program:\n%s\n", &ProgramErrorMessage[0]);
		CHECK_GL(glGetError(), "Failed to validate program.");
	}

	//Get uniform locations
	for (UniformLocation* loc : uniformLocations) {
		GLint location = glGetUniformLocation(id, loc->name.c_str());
		if (location == -1) {
			LOGGER->warn("Uniform location %s is not found in shader.", loc->name.c_str());
		}
		else {
			loc->location = location;
		}
	}
}

void GL_Pipeline::bind() {
	glUseProgram(id);
	CHECK_GL(glGetError(), "Failed to use program.");
}

void GL_Pipeline::unbind() {
	glUseProgram(0);
	CHECK_GL(glGetError(), "Failed to use program.");
}

void GL_Pipeline::addUniformLocation(std::string name) {
	UniformLocation* loc = new UniformLocation();
	loc->name = name;
	loc->location = -1;
	uniformLocations.push_back(loc);
}

void GL_Pipeline::loadUniform(std::string name, float v1) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform1f(load, v1);
			return;
		}
	}

	LOGGER->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, float v1, float v2) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform2f(load, v1, v2);
			return;
		}
	}

	LOGGER->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, float v1, float v2, float v3) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform3f(load, v1, v2, v3);
			return;
		}
	}

	LOGGER->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, float v1, float v2, float v3, float v4) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform4f(load, v1, v2, v3, v4);
			return;
		}
	}

	LOGGER->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, Mat4* matrix) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniformMatrix4fv(load, 1, GL_TRUE, matrix->get());
			return;
		}
	}

	LOGGER->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::addVertexInput(VertexInput* input){
	vertexInputs.push_back(input);
}