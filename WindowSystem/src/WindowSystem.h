#pragma once

#include "InputSystem.h"

#include "FierceWindow.h"
#include "WindowError.h"

#include <Windows.h>
#include <windowsx.h>

class WindowSystem {
public:
	WindowSystem(InputSystem* inputSystem);
	~WindowSystem();

	void createWindow(WINDOW_MODE mode, int width, int height);
	void createDummyWindow(WINDOW_MODE mode, int width, int height);

	FierceWindow* getWindow() { return m_window; }
	FierceWindow* getDummyWindow() { return m_dummyWindow; }

	MAPPING getMapping(WPARAM key) {
		std::map<WPARAM,MAPPING>::iterator it;
		it = mappings.find(key);
		if(it==mappings.end()) {
			return MAPPING::NONE;
		}
		else {
			return it->second;
		}
	};

private:
	WINDOW_ERROR registerWindowClass(LPCWSTR className, WNDPROC wndProc);
	WINDOW_ERROR unregisterWindowClass(LPCWSTR className);

private:
	InputSystem* m_inputSystem;
	std::map<WPARAM, MAPPING> mappings;

	HINSTANCE hInstance = nullptr;
	LPCWSTR fierceWindowClassName = L"FierceWindow";
	LPCWSTR fierceDummyWindowClassName = L"FierceDummyWindow";

	FierceWindow* m_window = nullptr;
	FierceWindow* m_dummyWindow = nullptr;

public:
	int m_x_alt = 0;
	int m_y_alt = 0;
	bool first = true;
};