#include "FunctionLoader.h"

//General
PFN_RENDERER_INIT_PROC renderer_init;
PFN_RENDERER_START_FRAME_PROC renderer_startFrame;
PFN_RENDERER_ADD_ENTITY_PROC renderer_addEntity;
PFN_RENDERER_END_FRAME_PROC renderer_endFrame;
PFN_RENDERER_CLEAN_UP_PROC renderer_cleanUp;

PFN_RENDERER_SET_ORTHOGRAPHIC_PROJECTION_PROC renderer_setOrthographicProjection;
PFN_RENDERER_SET_PERSPECTIVE_PROJECTION_PROC renderer_setPerspectiveProjection;

PFN_RENDERER_LOAD_MESH_PROC renderer_loadMesh;

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
	renderer_addEntity = (PFN_RENDERER_ADD_ENTITY_PROC)getFunctionPointer(renderer, "renderer_addEntity");
	renderer_endFrame = (PFN_RENDERER_END_FRAME_PROC)getFunctionPointer(renderer, "renderer_endFrame");
	renderer_cleanUp = (PFN_RENDERER_CLEAN_UP_PROC)getFunctionPointer(renderer,"renderer_cleanUp");

	renderer_setOrthographicProjection = (PFN_RENDERER_SET_ORTHOGRAPHIC_PROJECTION_PROC)getFunctionPointer(renderer,"renderer_setOrthographicProjection");
	renderer_setPerspectiveProjection = (PFN_RENDERER_SET_PERSPECTIVE_PROJECTION_PROC)getFunctionPointer(renderer, "renderer_setPerspectiveProjection");

	renderer_loadMesh = (PFN_RENDERER_LOAD_MESH_PROC)getFunctionPointer(renderer, "renderer_loadMesh");
}