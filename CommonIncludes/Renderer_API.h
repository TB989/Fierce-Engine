#pragma once

#include "windows.h"
#include <cstdint>
#include <string>

typedef uint32_t ShaderID;
typedef uint32_t PipelineID;

enum class ShaderType{
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	UNKNOWN
};

enum class Type {
	INT,FLOAT
};

struct VertexInput {
	std::string name;
	uint32_t location;
	uint32_t size;
	Type type;
};

enum class ParameterType {
	UNIFORM
};

static VertexInput POS2 = VertexInput{ "position", 0, 2, Type::FLOAT};

#ifdef DLL_EXPORT
	#define RENDERER_API extern "C" __declspec(dllexport)
#endif // DLL_EXPORT

#ifdef DLL_IMPORT
typedef bool (*PFN_INIT_RENDERER_PROC)(HWND dummyWindowHandle, HWND windowHandle);
typedef bool (*PFN_RENDER_PROC)();
typedef bool (*PFN_CLEAN_UP_RENDERER_PROC)();

typedef ShaderID (*PFN_ADD_SHADER_PROC)(ShaderType shaderType,int sourceCodeSize,char* sourceCode);

typedef PipelineID (*PFN_ADD_PIPELINE_PROC)(ShaderID vertexShader, ShaderID fragmentShader);
typedef void (*PFN_ADD_VERTEX_INPUT_PROC)(PipelineID id,VertexInput* input);
typedef void (*PFN_ADD_PIPELINE_PARAMETER_PROC)(PipelineID id, ParameterType type,char* name);
typedef void (*PFN_CREATE_PIPELINE_PROC)(PipelineID id);

extern PFN_INIT_RENDERER_PROC initRenderer;
extern PFN_RENDER_PROC render;
extern PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer;

extern PFN_ADD_SHADER_PROC addShader;

extern PFN_ADD_PIPELINE_PROC addPipeline;
extern PFN_ADD_VERTEX_INPUT_PROC addVertexInput;
extern PFN_ADD_PIPELINE_PARAMETER_PROC addPipelineParameter;
extern PFN_CREATE_PIPELINE_PROC createPipeline;

#endif // DLL_IMPORT