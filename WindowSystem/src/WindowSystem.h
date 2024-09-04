#pragma once

#include <Windows.h>
#include "Window.h"
#include "src/Logger.h"
#include "src/FierceStrings.h"
#include <vector>

namespace Fierce {

	typedef void (*FunctionPtr)();

	class WindowSystem {
	public:
		WindowSystem();
		~WindowSystem();

		void setWindowCloseFunction(FunctionPtr onWindowClosed) { m_onWindowClosed = onWindowClosed; }

		Window* createWindow(std::string title, Window::WINDOW_MODE windowMode, int width, int height);
		void deleteWindow(Window* window);

	private:
		void registerWindowClass(LPCWSTR className, WNDPROC wndProc);
		void unregisterWindowClass(LPCWSTR className);

	private:
		HINSTANCE hInstance = nullptr;
		LPCWSTR m_fierceWindowClassName = L"FierceWindow";
		std::vector<Window*> m_windows;

		Logger* m_logger;

	public:
		FunctionPtr m_onWindowClosed = nullptr;
	};

}//end namespace