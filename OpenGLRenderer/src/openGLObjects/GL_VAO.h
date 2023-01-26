#pragma once

#include "src/Common.h"
#include "OpenGLObject.h"

#include "GL_VBO.h"

class GL_VertexAttribute;

class GL_VAO {
public:
	GL_VAO(GL_VBO* vertexBuffer);
	GL_VAO(GL_VBO* vertexBuffer, GL_VBO* indexBuffer);
	~GL_VAO();
	void bind();
	void unbind();

	void addVertexAttribute(GL_VertexAttribute* attribute);
	void draw();
	void draw(GLsizei first, GLsizei count);
private:
	GLuint m_id;
	GL_VBO* m_vertexBuffer = nullptr;
	GL_VBO* m_indexBuffer = nullptr;
	std::vector<GL_VertexAttribute*> vertexAttributes;
	int numElements;
};