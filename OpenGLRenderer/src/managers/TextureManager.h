#pragma once

#include "src/Common.h"
#include "src/openGLObjects/GL_Texture.h"

class AssetManager;

class TextureManager {

public:
	TextureManager(AssetManager* assetManager);
	~TextureManager();

	int addTexture(GL_Texture* texture);
	GL_Texture* getTexture(int id) { return textures[id]; }

private:
	AssetManager* m_assetManager;
	std::unordered_map<int, GL_Texture*> textures;
	int nextTextureId = 0;
};
