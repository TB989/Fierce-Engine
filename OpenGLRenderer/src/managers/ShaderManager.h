#pragma once

#include "src/Common.h"

#include "src/openGLObjects/GL_Shader.h"

class AssetManager;

class ShaderManager {

public:
	ShaderManager(AssetManager* assetManager);
	~ShaderManager();

	void addShader(std::string name,GL_Shader* shader);
	GL_Shader* getShader(std::string name) { return shaders[name]; }

private:
	AssetManager* m_assetManager;
	std::unordered_map<std::string,GL_Shader*> shaders;
};