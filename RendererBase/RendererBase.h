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

enum RenderType {
	SIMPLE_COLOR_2D,
	SIMPLE_COLOR_3D,
	GEOMETRY_2D,
	GEOMETRY_3D
};

#ifdef DLL_EXPORT
	#define RENDERER_API extern "C" __declspec(dllexport)
#endif // DLL_EXPORT

#ifdef DLL_IMPORT
	typedef void (*PFN_RENDERER_INIT_PROC)(HWND dummyWindowHandle, HWND windowHandle);
	typedef void (*PFN_RENDERER_START_FRAME_PROC)();
	typedef void (*PFN_RENDERER_ADD_ENTITY_PROC)(RenderType renderType,float &modelMatrix,int meshID,float &color);
	typedef void (*PFN_RENDERER_END_FRAME_PROC)();
	typedef void (*PFN_RENDERER_CLEAN_UP_PROC)();

	typedef void (*PFN_RENDERER_SET_ORTHOGRAPHIC_PROJECTION_PROC)(float width,float height,float n,float f);
	typedef void (*PFN_RENDERER_SET_PERSPECTIVE_PROJECTION_PROC)(float aspect,float fov,float n,float f);

	typedef int (*PFN_RENDERER_LOAD_MESH_PROC)(MeshSettings settings,int numVertices, float *vertices, int numIndices, unsigned int *indices);

//##########################################################################################################################
	extern PFN_RENDERER_INIT_PROC renderer_init;
	extern PFN_RENDERER_START_FRAME_PROC renderer_startFrame;
	extern PFN_RENDERER_ADD_ENTITY_PROC renderer_addEntity;
	extern PFN_RENDERER_END_FRAME_PROC renderer_endFrame;
	extern PFN_RENDERER_CLEAN_UP_PROC renderer_cleanUp;

	extern PFN_RENDERER_SET_ORTHOGRAPHIC_PROJECTION_PROC renderer_setOrthographicProjection;
	extern PFN_RENDERER_SET_PERSPECTIVE_PROJECTION_PROC renderer_setPerspectiveProjection;

	extern PFN_RENDERER_LOAD_MESH_PROC renderer_loadMesh;
#endif // DLL_IMPORT