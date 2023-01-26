#pragma once

#include "src/Common.h"
#include "src/GL_Include.h"

#include "GL_Renderer.h"
#include "GL_Pipeline.h"

class GL_Renderer_Color2D:public GL_Renderer{

public:
	GL_Renderer_Color2D(GL_Pipeline* pipeline);

public:
	void render();

private:
	GL_Pipeline* m_pipeline;
};