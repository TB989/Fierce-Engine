#pragma once

#include "src/Common.h"
#include "OpenGLObject.h"

class GL_Texture : public OpenGLObject {
public:
	GL_Texture(GLenum target);
	~GL_Texture();
	void bind();
	void unbind();
	void loadData(GLsizei width, GLsizei height, unsigned char* data);

private:
	GLenum m_target;
	GLuint m_id;
};