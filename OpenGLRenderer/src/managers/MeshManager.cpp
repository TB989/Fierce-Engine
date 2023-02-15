#include "MeshManager.h"

MeshManager::MeshManager(AssetManager* assetManager){
    m_assetManager = assetManager;
}

MeshManager::~MeshManager() {
	for (auto& mesh : meshes) {
		delete mesh.second;
	}
	meshes.clear();
}

int MeshManager::addMesh(Mesh* mesh) {
    nextMeshId++;
	meshes[nextMeshId] = mesh;
    return nextMeshId;
}

Mesh::Mesh(MeshSettings settings, int numVertices, float* vertices, int numIndices, unsigned int* indices){
    vertexBuffer = new GL_VBO(GL_ARRAY_BUFFER);
    indexBuffer = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);

    vertexBuffer->loadData(numVertices * sizeof(float), vertices, GL_STATIC_DRAW);
    indexBuffer->loadData(numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    vao = new GL_VAO(vertexBuffer, indexBuffer);
    if (settings.is2D) {
        vao->addVertexAttribute(GL_VertexAttribute::POS2);
    }
    else {
        vao->addVertexAttribute(GL_VertexAttribute::POS3);
    }
    if (settings.hasColor) {
        vao->addVertexAttribute(GL_VertexAttribute::COLOR);
    }
    if (settings.hasTextureCoordinates) {
        vao->addVertexAttribute(GL_VertexAttribute::TEX);
    }
    if (settings.hasNormals) {
        vao->addVertexAttribute(GL_VertexAttribute::NORMAL);
    }
}

Mesh::~Mesh(){
    vao->unbind();
    delete vao;
    vertexBuffer->unbind();
    delete vertexBuffer;
    indexBuffer->unbind();
    delete indexBuffer;
}

void Mesh::bind(){
    vao->bind();
}

void Mesh::render(){
    vao->draw();
}

void Mesh::unbind(){
    vao->unbind();
}