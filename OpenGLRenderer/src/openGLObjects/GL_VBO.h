#pragma once

#include "Common.h"
#include "OpenGLObject.h"

class GL_VBO : public OpenGLObject{
public:
	GL_VBO(GLenum type);
	~GL_VBO();
	void bind();
	void unbind();

	GLsizeiptr getSize() { return m_size; }

	void loadData(GLsizeiptr size, const void* data, GLenum usage);
private:
	GLenum m_type;
	GLuint m_id;
	GLsizeiptr m_size;
};