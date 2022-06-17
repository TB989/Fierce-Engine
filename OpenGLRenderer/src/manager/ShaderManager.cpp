#include "ShaderManager.h"

ShaderManager::ShaderManager(){

}

ShaderManager::~ShaderManager() {
	for (auto& shader : ID_Shader_map) {
		delete shader.second;
	}
}

ShaderID ShaderManager::addShader(ShaderType shaderType, int sourceCodeSize, char* sourceCode) {
	counter++;
	GL_Shader* shader = new GL_Shader(shaderType);
	shader->addSourceCode(sourceCodeSize,sourceCode);
	shader->create();
	ID_Shader_map[counter] = shader;
	return counter;
}