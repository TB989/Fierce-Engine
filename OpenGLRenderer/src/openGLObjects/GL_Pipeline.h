#pragma once

#include "src/Common.h"
#include "OpenGLObject.h"

#include "MathLibrary.h"

#include "RendererBase.h"

class GL_Shader;
class GL_VertexAttribute;

class GL_Pipeline : public OpenGLObject{
public:
	GL_Pipeline(GL_Shader* shader1, GL_Shader* shader2);
	GL_Pipeline(GL_Shader* shader1, GL_Shader* shader2, GL_Shader* shader3);
	~GL_Pipeline();

	void create();

	void bind();
	void unbind();

	void addUniformLocation(std::string name);
	void loadUniform(std::string location, float v1);
	void loadUniform(std::string location, float v1, float v2);
	void loadUniform(std::string location, float v1, float v2, float v3);
	void loadUniform(std::string location, float v1, float v2, float v3, float v4);
	void loadUniform(std::string location, Mat4* matrix);

private:
	struct UniformLocation {
		std::string name;
		GLint location;
	};

private:
	GLuint id;
	std::vector<GL_Shader*> shaderList;

	std::vector<UniformLocation*> uniformLocations;
};