#pragma once

#include <Windows.h>

class GL_Context{
public:
	GL_Context();
	~GL_Context();

	void swapBuffers();

private:

	void createDummyContext();
	void deleteDummyContext();

	void createContext();
	void deleteContext();

private:
	HWND dummyHandle = nullptr;
	HDC dummyHDC = nullptr;
	HGLRC dummyContext = nullptr;

	HWND windowHandle = nullptr;
	HDC openGLHDC = nullptr;
	HGLRC openGLContext = nullptr;
};