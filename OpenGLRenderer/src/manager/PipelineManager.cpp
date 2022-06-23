#include "PipelineManager.h"

PipelineManager::PipelineManager() {

}

PipelineManager::~PipelineManager() {
	for (auto& pipeline : ID_Pipeline_map) {
		delete pipeline.second;
	}
}

PipelineID PipelineManager::addPipeline(GL_Shader* vertexShader, GL_Shader* fragmentShader) {
	counter++;
	GL_Pipeline* pipeline = new GL_Pipeline(vertexShader,fragmentShader);
	ID_Pipeline_map[counter] = pipeline;
	return counter;
}