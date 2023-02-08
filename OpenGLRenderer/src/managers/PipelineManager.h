#pragma once

#include "src/Common.h"

#include "src/openGLObjects/GL_Pipeline.h"

class PipelineManager {

public:
	PipelineManager()=default;
	~PipelineManager();

	void addPipeline(std::string name, GL_Pipeline* pipeline);
	GL_Pipeline* getPipeline(std::string name) { return pipelines[name]; }

private:
	std::unordered_map<std::string, GL_Pipeline*> pipelines;
};