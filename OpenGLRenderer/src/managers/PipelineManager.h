#pragma once

#include "src/Common.h"

#include "src/openGLObjects/GL_Pipeline.h"

class AssetManager;

class PipelineManager {

public:
	PipelineManager(AssetManager* assetManager);
	~PipelineManager();

	void addPipeline(std::string name, GL_Pipeline* pipeline);
	GL_Pipeline* getPipeline(std::string name) { return pipelines[name]; }

private:
	AssetManager* m_assetManager;
	std::unordered_map<std::string, GL_Pipeline*> pipelines;
};