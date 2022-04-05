#include "GL_Context.h"

#include "Main.h"
#include "WGL_FunctionLoader.h"
#include "GL_FunctionLoader.h"
#include "GL_Include.h"

GL_Context::GL_Context(){

	Main::LOGGER->info("Creating dummy context.");
	createDummyContext();
	Main::LOGGER->info("Loading WGL functions.");
	loadAllWGLFunctions();
	Main::LOGGER->info("Deleting dummy context.");
	deleteDummyContext();

	Main::LOGGER->info("Creating openGL context.");
	createContext();
	Main::LOGGER->info("Loading openGL functions.");
	loadAllGLFunctions();
}

GL_Context::~GL_Context() {
	deleteContext();
}

void GL_Context::swapBuffers() {
	if (!SwapBuffers(openGLHDC)) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR,"Failed to swap buffers.");
	}
}

void GL_Context::createDummyContext() {
	dummyHDC = GetDC(dummyHandle);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;

	int format = ChoosePixelFormat(dummyHDC, &pfd);
	if (!format) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to find pixel format for dummy context.");
	}
	if (!SetPixelFormat(dummyHDC, format, &pfd)) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to set pixel format for dummy context.");
	}

	dummyContext = wglCreateContext(dummyHDC);
	if (!dummyContext) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to create dummy context.");
	}
	if (!wglMakeCurrent(dummyHDC, dummyContext)) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed make dummy context current.");
	}
}

void GL_Context::deleteDummyContext() {
	wglMakeCurrent(dummyHDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dummyHandle, dummyHDC);
}

void GL_Context::createContext() {
	openGLHDC = GetDC(windowHandle);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;

	int pixel_format_attribs[] = {
		WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
		WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,         32,
		WGL_ALPHA_BITS_ARB,         8,
		WGL_DEPTH_BITS_ARB,         24,
		WGL_STENCIL_BITS_ARB,       8,
		0
	};
	int pixel_format;
	UINT num_formats;
	wglChoosePixelFormatARB(openGLHDC, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
	if (!num_formats) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to choose pixel format.");
	}
	DescribePixelFormat(openGLHDC, pixel_format, sizeof(pfd), &pfd);
	if (!SetPixelFormat(openGLHDC, pixel_format, &pfd)) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to set pixel format.");
	}

	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,
	};
	openGLContext = wglCreateContextAttribsARB(openGLHDC, 0, attribs);
	if (!openGLContext) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to create context.");
	}
	if (!wglMakeCurrent(openGLHDC, openGLContext)) {
		//CHECK_FIERCE(FE_CONTEXT_ERROR, "Failed to make current context.");
	}
}

void GL_Context::deleteContext() {
	wglMakeCurrent(openGLHDC, 0);
	wglDeleteContext(openGLContext);
	ReleaseDC(windowHandle, openGLHDC);
}