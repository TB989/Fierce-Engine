#include "GL_VBO.h"

GL_VBO::GL_VBO(GLenum type) {
	m_type = type;
	glGenBuffers(1, &m_id);
	CHECK_GL(glGetError(), "Failed to generate buffer.");
}

GL_VBO::~GL_VBO() {
	glDeleteBuffers(1, &m_id);
	CHECK_GL(glGetError(), "Failed to delete buffer.");
}

void GL_VBO::bind() {
	glBindBuffer(m_type, m_id);
	CHECK_GL(glGetError(), "Failed to bind buffer.");
}

void GL_VBO::unbind() {
	glBindBuffer(m_type, 0);
	CHECK_GL(glGetError(), "Failed to unbind buffer.");
}

void GL_VBO::loadData(GLsizeiptr size, const void* data, GLenum usage) {
	m_size = size;
	glBindBuffer(m_type, m_id);
	CHECK_GL(glGetError(), "Failed to bind buffer.");
	glBufferData(m_type, size, data, usage);
	CHECK_GL(glGetError(), "Failed to buffer data.");
	glBindBuffer(m_type, 0);
	CHECK_GL(glGetError(), "Failed to unbind buffer.");
}