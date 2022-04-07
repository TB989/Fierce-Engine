#pragma once

#include "core/EngineSettings.h"
#include "core/FierceExceptions.h"

#include <Windows.h>
#include <windowsx.h>
#include <map>

class FierceWindow;

class WindowSystem {
public:
	WindowSystem(EngineSettings* settings);
	~WindowSystem();

	FierceWindow* getWindow() { return m_window; }
	FierceWindow* getDummyWindow() { return m_dummyWindow; }

private:
	FIERCE_ERROR registerWindowClass(LPCWSTR className, WNDPROC wndProc);
	FIERCE_ERROR unregisterWindowClass(LPCWSTR className);

private:
	EngineSettings* m_settings = {};

	HINSTANCE hInstance = nullptr;
	LPCWSTR fierceWindowClassName = L"FierceWindow";
	LPCWSTR fierceDummyWindowClassName = L"FierceDummyWindow";

	FierceWindow* m_window = nullptr;
	FierceWindow* m_dummyWindow = nullptr;
};