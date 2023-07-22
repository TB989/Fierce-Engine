#include "GL_Texture.h"

GL_Texture::GL_Texture(GLenum target){
	m_target = target;
	glGenTextures(1, &m_id);
	CHECK_GL(glGetError(), "Failed to generate texture.");
}

GL_Texture::~GL_Texture(){
	glDeleteTextures(1,&m_id);
	CHECK_GL(glGetError(), "Failed to delete texture.");
}

void GL_Texture::bind(){
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(m_target, m_id);
	CHECK_GL(glGetError(), "Failed to bind texture.");
}

void GL_Texture::unbind(){
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(m_target, 0);
	CHECK_GL(glGetError(), "Failed to unbind texture.");
}

void GL_Texture::loadData(GLsizei width,GLsizei height, unsigned char* data){
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(m_target, m_id);
	CHECK_GL(glGetError(), "Failed to bind texture.");
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexImage2D(m_target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	CHECK_GL(glGetError(), "Failed to load data.");
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(m_target, 0);
	CHECK_GL(glGetError(), "Failed to unbind texture.");
}