#pragma once

#include <Windows.h>
#include "Window.h"
#include "src/FierceStrings.h"
#include "src/System.h"
#include <vector>
#include <unordered_map>

#include "src/InputSystem.h"

namespace Fierce {

	typedef void (*FunctionPtr)();

	class LoggingSystem;
	enum BINDING;

	class WindowSystem :public System{
	public:
		WindowSystem(LoggingSystem* loggingSystem,InputSystem* inputSystem);
		~WindowSystem();

		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Window* createWindow(std::string title, Window::WINDOW_MODE windowMode, int width, int height);
		void deleteWindow(Window* window);

	private:
		void registerWindowClass(LPCWSTR className, WNDPROC wndProc);
		void unregisterWindowClass(LPCWSTR className);

	private:
		HINSTANCE hInstance = nullptr;
		LPCWSTR m_fierceWindowClassName = L"FierceWindow";
		std::vector<Window*> m_windows;

		LoggingSystem* m_loggingSystem=nullptr;
		Logger* m_logger=nullptr;

		InputSystem* m_inputSystem=nullptr;

	public:
		static std::unordered_map<int, BINDING> m_bindings;
	};

}//end namespace