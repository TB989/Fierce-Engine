#pragma once

#include "src/Common.h"

#include "src/core/EngineSettings.h"
#include "src/core/FierceExceptions.h"

class FierceWindow {
public:
	FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings* settings, bool dummy);
	~FierceWindow();

	void pollEvents();
	void show();

	HWND getHandle() { return windowHandle; }
private:
	FIERCE_ERROR createWindow(LPCWSTR className, LPCWSTR title, EngineSettings* settings, bool dummy);
	FIERCE_ERROR destroyWindow();
private:
	HWND windowHandle = nullptr;
};

