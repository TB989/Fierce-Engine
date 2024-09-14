#pragma once

#include <Windows.h>
#include "Window.h"
#include "src/FierceStrings.h"
#include "src/System.h"
#include <vector>

namespace Fierce {

	typedef void (*FunctionPtr)();

	class LoggingSystem;

	class WindowSystem :public System{
	public:
		WindowSystem(LoggingSystem* loggingSystem);
		~WindowSystem();

		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

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

		LoggingSystem* m_loggingSystem;
		Logger* m_logger;

	public:
		FunctionPtr m_onWindowClosed = nullptr;
	};

}//end namespace