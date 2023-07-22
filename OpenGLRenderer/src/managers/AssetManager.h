#pragma once

#include "ShaderManager.h"
#include "PipelineManager.h"
#include "MeshManager.h"
#include "TextureManager.h"

class AssetManager {
public:
	AssetManager();
	~AssetManager();

	void loadShaders();
	void loadPipelines();
	void loadRenderers();

	int loadMesh(MeshSettings settings, int numVertices, float* vertices, int numIndices, unsigned int* indices);
	int loadTexture(int width, int height, unsigned char* data);

	ShaderManager* getShaderManager() { return shaderManager; }
	PipelineManager* getPipelineManager() { return pipelineManager; }
	MeshManager* getMeshManager() { return meshManager; }
	TextureManager* getTextureManager() { return textureManager; }

private:
	ShaderManager* shaderManager;
	PipelineManager* pipelineManager;

	MeshManager* meshManager;
	TextureManager* textureManager;
};