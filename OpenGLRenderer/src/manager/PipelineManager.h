#pragma once

#include "Common.h"

#include "openGLObjects/GL_Pipeline.h"
#include "openGLObjects/GL_Shader.h"

class PipelineManager {
public:
	PipelineManager();
	~PipelineManager();

	GL_Pipeline* getPipeline(PipelineID id) { return ID_Pipeline_map[id]; }

	PipelineID addPipeline(GL_Shader* vertexShader,GL_Shader* fragmentShader);

private:

	uint32_t counter = 0;
	std::unordered_map<uint32_t, GL_Pipeline*> ID_Pipeline_map;

};