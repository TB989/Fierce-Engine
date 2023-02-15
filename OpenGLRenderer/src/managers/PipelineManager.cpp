#include "PipelineManager.h"

PipelineManager::PipelineManager(AssetManager* assetManager){
	m_assetManager = assetManager;
}

PipelineManager::~PipelineManager() {
	for (auto& pipeline : pipelines) {
		delete pipeline.second;
	}
	pipelines.clear();
}

void PipelineManager::addPipeline(std::string name, GL_Pipeline* pipeline) {
	if (pipelines.find(name) == pipelines.end()) {
		pipelines[name] = pipeline;
	}
}