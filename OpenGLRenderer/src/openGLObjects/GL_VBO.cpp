#include "GL_VBO.h"

GL_VBO::GL_VBO(GLenum type) {
	m_type = type;
	glGenBuffers(1, &m_id);
}

GL_VBO::~GL_VBO() {
	glDeleteBuffers(1, &m_id);
}

void GL_VBO::bind() {
	glBindBuffer(m_type, m_id);
}

void GL_VBO::unbind() {
	glBindBuffer(m_type, 0);
}

void GL_VBO::loadData(GLsizeiptr size, const void* data, GLenum usage) {
	m_size = size;
	glBindBuffer(m_type, m_id);
	glBufferData(m_type, size, data, usage);
	glBindBuffer(m_type, 0);
}