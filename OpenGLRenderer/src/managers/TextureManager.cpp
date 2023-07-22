#include "TextureManager.h"

TextureManager::TextureManager(AssetManager* assetManager) {
    m_assetManager = assetManager;
}

TextureManager::~TextureManager() {
    for (auto& texture : textures) {
        delete texture.second;
    }
    textures.clear();
}

int TextureManager::addTexture(GL_Texture* texture) {
    nextTextureId++;
    textures[nextTextureId] = texture;
    return nextTextureId;
}