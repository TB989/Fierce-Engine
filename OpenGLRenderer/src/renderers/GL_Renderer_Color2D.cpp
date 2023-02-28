#include "GL_Renderer_Color2D.h"

/**GL_Renderer_Color2D::GL_Renderer_Color2D(AssetManager* assetManager, GL_Pipeline* pipeline) {
	m_assetManager = assetManager;
	m_pipeline = pipeline;
}

GL_Renderer_Color2D::~GL_Renderer_Color2D(){
	clear();
	m_pipeline = nullptr;
}

void GL_Renderer_Color2D::addEntity(float* modelMatrix, int meshId, float* color){
	GL_Renderbatch_Color2D* renderbatch = findRenderbatch(meshId,color);
	if (renderbatch == nullptr) {
		renderbatch = new GL_Renderbatch_Color2D(meshId,color);
		renderbatches.push_back(renderbatch);
	}
	renderbatch->addEntity(modelMatrix);
}

void GL_Renderer_Color2D::clear(){
	for (auto renderbatch:renderbatches) {
		renderbatch->clear();
	}
}

void GL_Renderer_Color2D::render(){
	TODO bind projection matrix
	m_pipeline->bind();
	for (auto renderbatch : renderbatches) {
		Mesh* mesh = m_assetManager->getMeshManager()->getMesh(renderbatch->getMesh());
		Color3f* color = renderbatch->getColor();
		std::vector<Mat4*> modelMatrices;

		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->bind();
		for (auto modelMatrix:modelMatrices) {
			m_pipeline->loadUniform("modelMatrix",modelMatrix);
			mesh->render();
		}
		mesh->unbind();
	}
	m_pipeline->unbind();
}

GL_Renderbatch_Color2D* GL_Renderer_Color2D::findRenderbatch(int meshId, float* color){
	TODO
	for (auto renderbatch : renderbatches) {
		return nullptr;
	}
	return nullptr;
}

//################################################################################################

GL_Renderbatch_Color2D::GL_Renderbatch_Color2D(int mesh, float* color){
	m_color = new Color3f(color);
	m_mesh = mesh;
}

GL_Renderbatch_Color2D::~GL_Renderbatch_Color2D(){
	clear();
	delete m_color;
	m_color = nullptr;
	m_mesh = -1;
}

void GL_Renderbatch_Color2D::addEntity(float* modelMatrix){
	Mat4* matrix = new Mat4(modelMatrix);
	modelMatrices.push_back(matrix);
}

void GL_Renderbatch_Color2D::clear(){
	for (auto modelMatrix : modelMatrices) {
		delete modelMatrix;
	}
	modelMatrices.clear();
}*/