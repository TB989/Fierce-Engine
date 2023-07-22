#pragma once

#include "WindowError.h"

#include <Windows.h>

enum WINDOW_MODE {
	HEADLESS,
	WINDOWED,
	FULLSCREEN
};

class FierceWindow {
public:
	FierceWindow(LPCWSTR className, LPCWSTR title, WINDOW_MODE mode, int width, int height, bool dummy);
	~FierceWindow();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	void registerForRawInput();

	void pollEvents();
	void show();

	HWND getHandle() { return windowHandle; }
private:
	WINDOW_ERROR createWindow(LPCWSTR className, LPCWSTR title, WINDOW_MODE mode, int width, int height, bool dummy);
	void clipCursor();
	WINDOW_ERROR destroyWindow();
private:
	HWND windowHandle = nullptr;
	int m_width;
	int m_height;
};

