#pragma once

#include "Common.h"
#include "GL_Include.h"

class GL_VBO {
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