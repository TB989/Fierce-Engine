#pragma once

#include "Common.h"

class GL_Context{
public:
	GL_Context(HWND dummyWindowHandle,HWND windowHandle);
	~GL_Context();

	void swapBuffers();

private:

	void createDummyContext();
	void deleteDummyContext();

	void createContext();
	void deleteContext();

private:
	HWND m_dummyHandle = nullptr;
	HDC dummyHDC = nullptr;
	HGLRC dummyContext = nullptr;

	HWND m_windowHandle = nullptr;
	HDC openGLHDC = nullptr;
	HGLRC openGLContext = nullptr;
};