#pragma once

/**#include "src/Common.h"
#include "src/GL_Include.h"

#include "GL_Renderer.h"
#include "src/openGLObjects/GL_Pipeline.h"

class GL_Renderer_Geometry2D :public GL_Renderer {
public:
	GL_Renderer_Geometry2D(GL_Pipeline* pipeline);

public:
	void addEntity(Entity2D* entity) { entities.push_back(entity); }
	void render();

private:
	GL_Pipeline* m_pipeline;
	std::vector<Entity2D*> entities;

	void renderEntity(Entity2D* entity);
};*/