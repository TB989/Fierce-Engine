#pragma once

#include "Common.h"

#include "openGLObjects/GL_Shader.h"
#include "openGLObjects/GL_Pipeline.h"
#include "openGLObjects/GL_VBO.h"
#include "openGLObjects/GL_VAO.h"

GL_Shader* vertexShader;
GL_Shader* fragmentShader;
GL_Pipeline* pipeline;
GL_VBO* vertexBuffer;
GL_VBO* indexBuffer;
GL_VAO* vao;