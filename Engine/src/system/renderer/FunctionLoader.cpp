#include "FunctionLoader.h"

//General
PFN_RENDERER_INIT_PROC renderer_init;
PFN_RENDERER_START_FRAME_PROC renderer_startFrame;
PFN_RENDERER_ADD_ENTITY_COLOR_PROC renderer_addEntityColor;
PFN_RENDERER_ADD_ENTITY_NORMAL_PROC renderer_addEntityNormal;
PFN_RENDERER_ADD_ENTITY_TEXTURE_PROC renderer_addEntityTexture;
PFN_RENDERER_ADD_ENTITY_GEOMETRY_PROC renderer_addEntityGeometry;
PFN_RENDERER_END_FRAME_PROC renderer_endFrame;
PFN_RENDERER_CLEAN_UP_PROC renderer_cleanUp;

PFN_RENDERER_SET_ORTHOGRAPHIC_PROJECTION_PROC renderer_setOrthographicProjection;
PFN_RENDERER_SET_PERSPECTIVE_PROJECTION_PROC renderer_setPerspectiveProjection;

PFN_RENDERER_SET_VIEW_MATRIX_PROC renderer_setViewMatrix;

PFN_RENDERER_LOAD_MESH_PROC renderer_loadMesh;

PFN_RENDERER_LOAD_TEXTURE_PROC renderer_loadTexture;

void* getFunctionPointer(HINSTANCE renderer,const char* name) {
	void* p = (void*)GetProcAddress(renderer,name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		LOGGER->error("Failed to load function %s.", name);
	}

	return p;
}

void loadAllFunctions(HINSTANCE renderer) {
	renderer_init = (PFN_RENDERER_INIT_PROC)getFunctionPointer(renderer,"renderer_init");
	renderer_startFrame = (PFN_RENDERER_START_FRAME_PROC)getFunctionPointer(renderer,"renderer_startFrame");
	renderer_addEntityColor = (PFN_RENDERER_ADD_ENTITY_COLOR_PROC)getFunctionPointer(renderer, "renderer_addEntityColor");
	renderer_addEntityNormal = (PFN_RENDERER_ADD_ENTITY_NORMAL_PROC)getFunctionPointer(renderer, "renderer_addEntityNormal");
	renderer_addEntityTexture = (PFN_RENDERER_ADD_ENTITY_TEXTURE_PROC)getFunctionPointer(renderer, "renderer_addEntityTexture");
	renderer_addEntityGeometry = (PFN_RENDERER_ADD_ENTITY_GEOMETRY_PROC)getFunctionPointer(renderer, "renderer_addEntityGeometry");
	renderer_endFrame = (PFN_RENDERER_END_FRAME_PROC)getFunctionPointer(renderer, "renderer_endFrame");
	renderer_cleanUp = (PFN_RENDERER_CLEAN_UP_PROC)getFunctionPointer(renderer,"renderer_cleanUp");

	renderer_setOrthographicProjection = (PFN_RENDERER_SET_ORTHOGRAPHIC_PROJECTION_PROC)getFunctionPointer(renderer,"renderer_setOrthographicProjection");
	renderer_setPerspectiveProjection = (PFN_RENDERER_SET_PERSPECTIVE_PROJECTION_PROC)getFunctionPointer(renderer, "renderer_setPerspectiveProjection");

	renderer_setViewMatrix=(PFN_RENDERER_SET_VIEW_MATRIX_PROC)getFunctionPointer(renderer, "renderer_setViewMatrix");

	renderer_loadMesh = (PFN_RENDERER_LOAD_MESH_PROC)getFunctionPointer(renderer, "renderer_loadMesh");

	renderer_loadTexture = (PFN_RENDERER_LOAD_TEXTURE_PROC)getFunctionPointer(renderer, "renderer_loadTexture");
}