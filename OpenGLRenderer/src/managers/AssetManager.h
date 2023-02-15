#pragma once

#include "ShaderManager.h"
#include "PipelineManager.h"
#include "RenderersManager.h"
#include "MeshManager.h"

class AssetManager {
public:
	AssetManager();
	~AssetManager();

	void loadShaders();
	void loadPipelines();
	void loadRenderers();

	int loadMesh(MeshSettings settings, int numVertices, float* vertices, int numIndices, unsigned int* indices);

	GL_Renderer* getRenderer(RenderType renderType) { return renderersManager->getRenderer(renderType); }

	ShaderManager* getShaderManager() { return shaderManager; }
	PipelineManager* getPipelineManager() { return pipelineManager; }
	RenderersManager* getRenderersManager() { return renderersManager; }
	MeshManager* getMeshManager() { return meshManager; }

private:
	ShaderManager* shaderManager;
	PipelineManager* pipelineManager;
	RenderersManager* renderersManager;

	MeshManager* meshManager;
};