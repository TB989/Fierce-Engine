#pragma once

#include "Common.h"
#include "GL_Include.h"

#include "GL_Renderer.h"
#include "GL_Pipeline.h"

class GL_Renderer_Color3D:public GL_Renderer{
public:
	GL_Renderer_Color3D(GL_Pipeline* pipeline);

public:
	//void addEntity(Entity3D* entity) { entities.push_back(entity); }
	void render();
	
private:
	GL_Pipeline* m_pipeline;
	//std::vector<Entity3D*> entities;
};