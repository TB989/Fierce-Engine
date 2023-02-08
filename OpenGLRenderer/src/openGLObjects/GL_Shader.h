#pragma once

#include "RendererBase.h"

#include "src/Common.h"
#include "OpenGLObject.h"

class GL_Shader : public OpenGLObject{
public:
	GL_Shader(GLenum type);
	~GL_Shader();

	GLuint getId() { return id; }

	void addSourceCode(std::string filename);
	void create();

private:
	GLuint id = -1;
};