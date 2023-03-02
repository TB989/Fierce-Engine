#pragma once

#include "src/Common.h"

#include "FierceWindow.h"
#include "src/core/EngineSettings.h"
#include "src/core/FierceExceptions.h"

#include <windowsx.h>

class Core;

class WindowSystem {
public:
	WindowSystem(EngineSettings* settings,Core* core);
	~WindowSystem();

	FierceWindow* getWindow() { return m_window; }
	FierceWindow* getDummyWindow() { return m_dummyWindow; }

	Core* getCore() { return m_core; }

	template<typename EventType>
	void postEvent(EventType* evnt) {
		m_core->eventSystem->postEvent(evnt);
	}

private:
	FIERCE_ERROR registerWindowClass(LPCWSTR className, WNDPROC wndProc);
	FIERCE_ERROR unregisterWindowClass(LPCWSTR className);

private:
	EngineSettings* m_settings = {};
	Core* m_core;

	HINSTANCE hInstance = nullptr;
	LPCWSTR fierceWindowClassName = L"FierceWindow";
	LPCWSTR fierceDummyWindowClassName = L"FierceDummyWindow";

	FierceWindow* m_window = nullptr;
	FierceWindow* m_dummyWindow = nullptr;
};