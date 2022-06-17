#include "..\..\..\OpenGLRenderer\src\manager\ShaderManager.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager(VK_Device* device){
	m_device = device;
}

ShaderManager::~ShaderManager(){
	deleteAllShaders();
}

uint32_t ShaderManager::addShader(ShaderType shaderType){
	shaders[counter] = new VK_Shader(m_device,shaderType);
	counter++;
	return counter;
}

void ShaderManager::createAllShaders(){
	for (auto& shader:shaders) {
		shader.second->create();
	}
}

void ShaderManager::deleteAllShaders(){
	for (auto& shader : shaders) {
		delete shader.second;
	}
}