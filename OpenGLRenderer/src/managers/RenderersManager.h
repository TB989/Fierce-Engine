#pragma once

#include "src/Common.h"

#include "src/renderers/GL_Renderer.h"

#include "RendererBase.h"

class AssetManager;

class RenderersManager {

public:
	RenderersManager(AssetManager* assetManager);
	~RenderersManager();

	void addRenderer(RenderType renderType, GL_Renderer* pipeline);
	GL_Renderer* getRenderer(RenderType renderType) { return renderers[renderType]; }

private:
	AssetManager* m_assetManager;
	std::unordered_map<RenderType, GL_Renderer*> renderers;
};
