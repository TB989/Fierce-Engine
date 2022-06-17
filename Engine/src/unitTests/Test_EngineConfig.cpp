#include "UnitTests.h"

#include "io/Parser.h"

Test_EngineConfig::Test_EngineConfig() {
    
}

void Test_EngineConfig::init() {

}

void Test_EngineConfig::update() {

}

void Test_EngineConfig::doRender() {

}

void Test_EngineConfig::cleanUp() {

}

void Test_EngineConfig::loadShaders() {
    std::vector<char> sourceCode;

    sourceCode=Parser::readText("C:/Users/tmbal/Desktop/Fierce-Engine/Engine/res/openGL/shaders/Shader_Color2D.vert");
    vertexShader = addShader(ShaderType::VERTEX_SHADER,sourceCode.size(), reinterpret_cast<char*>(sourceCode.data()));

    sourceCode = Parser::readText("C:/Users/tmbal/Desktop/Fierce-Engine/Engine/res/openGL/shaders/Shader_Color.frag");
    fragmentShader = addShader(ShaderType::FRAGMENT_SHADER,sourceCode.size(), reinterpret_cast<char*>(sourceCode.data()));
}

void Test_EngineConfig::loadPipelines() {
    PipelineID pipeline=addPipeline(vertexShader,fragmentShader);
}