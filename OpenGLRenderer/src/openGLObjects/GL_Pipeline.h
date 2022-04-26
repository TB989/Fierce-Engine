#pragma once

#include "Common.h"
#include "GL_Include.h"

#include "GL_Shader.h"
#include "GL_VertexAttribute.h"

class GL_Pipeline {
public:
	GL_Pipeline(std::string name, GL_Shader* shader1, GL_Shader* shader2);
	~GL_Pipeline();

	void create();

	void bind();
	void unbind();

	void addUniformLocation(std::string name);
	void loadUniform(std::string location, float v1);
	void loadUniform(std::string location, float v1, float v2);
	void loadUniform(std::string location, float v1, float v2, float v3);
	void loadUniform(std::string location, float v1, float v2, float v3, float v4);
	//void loadUniform(std::string location, Mat4* matrix);

	void addVertexAttribute(GL_VertexAttribute* attribute);

private:
	struct UniformLocation {
		std::string name;
		GLint location;
	};

private:
	GLuint id;
	std::string m_name;
	std::vector<GL_Shader*> shaderList;

	std::vector<UniformLocation*> uniformLocations;
	std::vector<GL_VertexAttribute*> vertexAttributes;
};