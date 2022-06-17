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
	pipeline->addVertexAttribute(GL_VertexAttribute::POS2);
	pipeline->addUniformLocation("color");
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->create();
	ID_Pipeline_map[counter] = pipeline;
	return counter;
}