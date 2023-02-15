#include "ShaderManager.h"

ShaderManager::ShaderManager(AssetManager* assetManager){
	m_assetManager = assetManager;
}

ShaderManager::~ShaderManager(){
	for (auto& shader : shaders) {
		delete shader.second;
	}
	shaders.clear();
}

void ShaderManager::addShader(std::string name, GL_Shader* shader){
	if (shaders.find(name)==shaders.end()) {
		shaders[name] = shader;
	}
}