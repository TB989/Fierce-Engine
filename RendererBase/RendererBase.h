#pragma once

#include "windows.h"
#include <cstdint>
#include <string>

struct MeshSettings {
	bool is2D;
	bool hasColor;
	bool hasTextureCoordinates;
	bool hasNormals;
};

#ifdef DLL_EXPORT
	#define RENDERER_API extern "C" __declspec(dllexport)
#endif // DLL_EXPORT

#ifdef DLL_IMPORT
	typedef bool (*PFN_INIT_RENDERER_PROC)(HWND dummyWindowHandle, HWND windowHandle);
	typedef bool (*PFN_RENDER_PROC)();
	typedef bool (*PFN_CLEAN_UP_RENDERER_PROC)();

	typedef int (*PFN_RENDERER_LOAD_MESH_PROC)(MeshSettings settings,int numVertices, float *vertices, int numIndices, unsigned int *indices);

	extern PFN_INIT_RENDERER_PROC initRenderer;
	extern PFN_RENDER_PROC render;
	extern PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer;

	extern PFN_RENDERER_LOAD_MESH_PROC renderer_loadMesh;
#endif // DLL_IMPORT