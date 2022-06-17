#pragma once

#include "Common.h"

#include "openGLObjects/GL_Shader.h"
#include "openGLObjects/GL_Pipeline.h"
#include "openGLObjects/GL_VBO.h"
#include "openGLObjects/GL_VAO.h"

#include "manager/ShaderManager.h"
#include "manager/PipelineManager.h"

#include "Matrix.h"
#include "Transform.h"

Transform2D transform;
Mat4 orthographicProjectionMatrix;
Mat4 modelMatrix;

GL_Pipeline* pipe;
GL_VBO* vertexBuffer;
GL_VBO* indexBuffer;
GL_VAO* vao;

ShaderManager* shaderManager;
PipelineManager* pipelineManager;