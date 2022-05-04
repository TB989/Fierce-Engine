#include "WGL_FunctionLoader.h"

wglCreateContextAttribsARB_type* wglCreateContextAttribsARB = nullptr;
wglChoosePixelFormatARB_type* wglChoosePixelFormatARB = nullptr;

void* getWGLFunctionPointer(const char* name) {
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		LOGGER->error("Failed to load function %s.", name);
		CHECK_GL(GL_CONTEXT_ERROR, "Failed to load WGL function.");
	}

	return p;
}

void loadAllWGLFunctions(){
	wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)getWGLFunctionPointer("wglCreateContextAttribsARB");
	wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)getWGLFunctionPointer("wglChoosePixelFormatARB");
}