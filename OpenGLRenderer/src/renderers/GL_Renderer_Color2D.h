#pragma once

/**#include "src/Common.h"
#include "src/GL_Include.h"

#include "MathLibrary.h"

#include "GL_Renderer.h"
#include "src/openGLObjects/GL_Pipeline.h"

#include "src/managers/AssetManager.h"

class GL_Renderbatch_Color2D :public GL_Renderbatch {

public:
	GL_Renderbatch_Color2D(int mesh,float* color);
	~GL_Renderbatch_Color2D();

	void addEntity(float* modelMatrix);
	void clear();

	Color3f* getColor() { return m_color; }
	int getMesh() { return m_mesh; }
	std::vector<Mat4*> getModelMatrices() { return modelMatrices; }

private:
	int m_mesh;
	Color3f* m_color;

	std::vector<Mat4*> modelMatrices;
};

class GL_Renderer_Color2D:public GL_Renderer{

public:
	GL_Renderer_Color2D(AssetManager* assetManager, GL_Pipeline* pipeline);
	~GL_Renderer_Color2D();

	void addEntity(float* modelMatrix, int meshId, float* color) override;
	void clear();

	void render();

private:
	AssetManager* m_assetManager;
	GL_Pipeline* m_pipeline;
	std::vector<GL_Renderbatch_Color2D*> renderbatches;

	GL_Renderbatch_Color2D* findRenderbatch(int meshId, float* color);
};*/