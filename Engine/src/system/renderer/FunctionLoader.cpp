#include "FunctionLoader.h"

#include "Renderer_API.h"

//General
PFN_INIT_RENDERER_PROC initRenderer;
PFN_RENDER_PROC render;
PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer;

void* getFunctionPointer(HINSTANCE renderer,const char* name) {
	void* p = (void*)GetProcAddress(renderer,name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		LOGGER->error("Failed to load function %s.", name);
	}

	return p;
}

void loadAllFunctions(HINSTANCE renderer) {
	initRenderer = (PFN_INIT_RENDERER_PROC)getFunctionPointer(renderer,"initRenderer");
	render = (PFN_RENDER_PROC)getFunctionPointer(renderer,"render");
	cleanUpRenderer = (PFN_CLEAN_UP_RENDERER_PROC)getFunctionPointer(renderer,"cleanUpRenderer");
}