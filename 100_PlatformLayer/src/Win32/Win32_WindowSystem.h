#pragma once

#include <vector>
#include <unordered_map>

#include "Windows.h"

#include "src/include/WindowSystem.h"

namespace Fierce {

	typedef void (*FunctionPtr)();

	class Logger;
	class LoggingSystem;
	class InputSystem;
	enum BINDING;

	class Win32_WindowSystem :public WindowSystem{
	public:
		Win32_WindowSystem(LoggingSystem* loggingSystem,InputSystem* inputSystem);
		~Win32_WindowSystem();

		void initSystem(std::string m_assetDirectory) override;
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