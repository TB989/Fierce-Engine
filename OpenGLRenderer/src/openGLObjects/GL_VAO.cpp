#include "GL_VAO.h"

GL_VAO::GL_VAO(GL_VBO* vertexBuffer) {
	glGenVertexArrays(1, &m_id);
	CHECK_GL(glGetError(), "Failed to generate vertex array.");
	m_vertexBuffer = vertexBuffer;
	numElements = vertexBuffer->getSize() / sizeof(GLfloat);
}

GL_VAO::GL_VAO(GL_VBO* vertexBuffer, GL_VBO* indexBuffer) {
	glGenVertexArrays(1, &m_id);
	CHECK_GL(glGetError(), "Failed to generate vertex array.");
	m_vertexBuffer = vertexBuffer;
	m_indexBuffer = indexBuffer;
	numElements = indexBuffer->getSize() / sizeof(GLuint);
}

GL_VAO::~GL_VAO() {
	glDeleteVertexArrays(1, &m_id);
	CHECK_GL(glGetError(), "Failed to delete vertex array.");
}

void GL_VAO::bind() {
	glBindVertexArray(m_id);
	CHECK_GL(glGetError(), "Failed to bind vertex array.");
}

void GL_VAO::unbind() {
	glBindVertexArray(0);
	CHECK_GL(glGetError(), "Failed to bind vertex array.");
}

void GL_VAO::addVertexAttribute(GL_VertexAttribute* attribute) {
	vertexAttributes.push_back(attribute);

	glBindVertexArray(m_id);
	CHECK_GL(glGetError(), "Failed to bind vertex array.");
	m_vertexBuffer->bind();
	if (m_indexBuffer != nullptr) {
		m_indexBuffer->bind();
	}

	GLsizei stride = 0;
	for (GL_VertexAttribute* attrib : vertexAttributes) {
		stride += attrib->getSize();
	}
	GLsizei offset = 0;
	for (GL_VertexAttribute* attrib : vertexAttributes) {
		glEnableVertexAttribArray(attrib->getLocation());
		CHECK_GL(glGetError(), "Failed to enable vertex array.");
		glVertexAttribPointer(attrib->getLocation(), attrib->getSize(), attrib->getType(), GL_FALSE, stride * sizeof(GLsizei), (GLvoid*)(offset * sizeof(GLsizei)));
		CHECK_GL(glGetError(), "Failed to setup attribute pointer.");
		offset += attrib->getSize();
	}

	glBindVertexArray(0);
	CHECK_GL(glGetError(), "Failed to bind vertex array.");
	m_vertexBuffer->unbind();
	if (m_indexBuffer != nullptr) {
		m_indexBuffer->unbind();
	}
}

void GL_VAO::draw() {
	if (m_indexBuffer == nullptr) {
		glDrawArrays(GL_TRIANGLES, 0, numElements);
		CHECK_GL(glGetError(), "Failed to draw arrays.");
	}
	else {
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, (void*)0);
		CHECK_GL(glGetError(), "Failed to draw elements.");
	}
}

void GL_VAO::draw(GLsizei first, GLsizei count) {
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(sizeof(GLsizei) * first));
	CHECK_GL(glGetError(), "Failed to draw elements.");
}