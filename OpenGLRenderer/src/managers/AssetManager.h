#pragma once

#include "ShaderManager.h"
#include "PipelineManager.h"
#include "MeshManager.h"

class AssetManager {
public:
	AssetManager();
	~AssetManager();

	void loadShaders();
	void loadPipelines();
	void loadRenderers();

	int loadMesh(MeshSettings settings, int numVertices, float* vertices, int numIndices, unsigned int* indices);

	ShaderManager* getShaderManager() { return shaderManager; }
	PipelineManager* getPipelineManager() { return pipelineManager; }
	MeshManager* getMeshManager() { return meshManager; }

private:
	ShaderManager* shaderManager;
	PipelineManager* pipelineManager;

	MeshManager* meshManager;
};