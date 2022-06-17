#pragma once

#include "windows.h"
#include <cstdint>

typedef uint32_t ShaderID;
typedef uint32_t PipelineID;

enum class ShaderType{
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	UNKNOWN
};

#ifdef DLL_EXPORT
	#define RENDERER_API extern "C" __declspec(dllexport)
#endif // DLL_EXPORT

#ifdef DLL_IMPORT
typedef bool (*PFN_INIT_RENDERER_PROC)(HWND dummyWindowHandle, HWND windowHandle);
typedef bool (*PFN_RENDER_PROC)();
typedef bool (*PFN_CLEAN_UP_RENDERER_PROC)();

typedef ShaderID (*PFN_ADD_SHADER_PROC)(ShaderType shaderType,int sourceCodeSize,char* sourceCode);
typedef PipelineID (*PFN_ADD_PIPELINE_PROC)(ShaderID vertexShader, ShaderID fragmentShader);

extern PFN_INIT_RENDERER_PROC initRenderer;
extern PFN_RENDER_PROC render;
extern PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer;

extern PFN_ADD_SHADER_PROC addShader;

extern PFN_ADD_PIPELINE_PROC addPipeline;
#endif // DLL_IMPORT