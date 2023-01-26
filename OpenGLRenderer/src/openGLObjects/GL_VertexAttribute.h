#pragma once

#include "src/Common.h"
#include "OpenGLObject.h"

class GL_VertexAttribute : public OpenGLObject{
public:
	static GL_VertexAttribute* POS2;
	static GL_VertexAttribute* POS3;
	static GL_VertexAttribute* TEX;
	static GL_VertexAttribute* NORMAL;
	static GL_VertexAttribute* COLOR;
public:
	GL_VertexAttribute(std::string name, GLuint location, GLint size, GLenum type);

	std::string getName() { return m_name; }
	GLuint getLocation() { return m_location; }
	GLint getSize() { return m_size; }
	GLenum getType() { return m_type; }
private:
	std::string m_name;
	GLuint m_location;
	GLint m_size;
	GLenum m_type;
};