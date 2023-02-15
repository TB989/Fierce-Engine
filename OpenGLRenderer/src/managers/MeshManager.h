#pragma once

#include "RendererBase.h"

#include "src/Common.h"

#include "src/openGLObjects/GL_Context.h"
#include "src/openGLObjects/GL_VBO.h"
#include "src/openGLObjects/GL_VAO.h"
#include "src/openGLObjects/GL_VertexAttribute.h"

class AssetManager;

class Mesh {

public:
	Mesh(MeshSettings settings, int numVertices, float* vertices, int numIndices, unsigned int* indices);
	~Mesh();

	void bind();
	void render();
	void unbind();

private:
	GL_VAO* vao;
	GL_VBO* vertexBuffer;
	GL_VBO* indexBuffer;
};

class MeshManager {

public:
	MeshManager(AssetManager* assetManager);
	~MeshManager();

	int addMesh(Mesh* mesh);
	Mesh* getMesh(int id) { return meshes[id]; }

private:
	AssetManager* m_assetManager;
	std::unordered_map<int, Mesh*> meshes;
	int nextMeshId = 0;
};
