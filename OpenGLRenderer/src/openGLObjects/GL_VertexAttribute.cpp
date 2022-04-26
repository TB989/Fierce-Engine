#include "GL_VertexAttribute.h"

GL_VertexAttribute::GL_VertexAttribute(std::string name, GLuint location, GLint size, GLenum type) {
	m_name = name;
	m_location = location;
	m_size = size;
	m_type = type;
}

GL_VertexAttribute* GL_VertexAttribute::POS2 = new GL_VertexAttribute("position", 0, 2, GL_FLOAT);
GL_VertexAttribute* GL_VertexAttribute::POS3 = new GL_VertexAttribute("position", 0, 3, GL_FLOAT);
GL_VertexAttribute* GL_VertexAttribute::TEX = new GL_VertexAttribute("textureCoordinate", 1, 2, GL_FLOAT);
GL_VertexAttribute* GL_VertexAttribute::NORMAL = new GL_VertexAttribute("normal", 2, 3, GL_FLOAT);
GL_VertexAttribute* GL_VertexAttribute::COLOR = new GL_VertexAttribute("color", 3, 3, GL_FLOAT);