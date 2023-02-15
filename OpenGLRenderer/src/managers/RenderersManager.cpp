#include "RenderersManager.h"

RenderersManager::RenderersManager(AssetManager* assetManager){
	m_assetManager = assetManager;
}

RenderersManager::~RenderersManager() {
	for (auto& renderer : renderers) {
		delete renderer.second;
	}
	renderers.clear();
}

void RenderersManager::addRenderer(RenderType renderType, GL_Renderer* renderer) {
	if (renderers.find(renderType) == renderers.end()) {
		renderers[renderType] = renderer;
	}
}