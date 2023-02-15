#pragma once

#include "GL_Renderer_Color2D.h"

class GL_Renderbatch {

};

class GL_Renderer{
public:
	virtual void addEntity(float* modelMatrix, int meshId, float* color)=0;
};