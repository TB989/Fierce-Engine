#pragma once

#include <vector>
#include <unordered_map>

#include "Windows.h"

#include "src/systems/IWindowSystem.h"
#include "src/systems/ILoggingSystem.h"
#include "src/systems/IInputSystem.h"

#include "src/PlatformLayer/InputSystem/InputContext.h"

namespace Fierce {

	typedef void (*FunctionPtr)();

	class Logger;
	class LoggingSystem;
	class InputSystem;
	enum BINDING;

	class Win32_WindowSystem :public IWindowSystem{
	public:
		Win32_WindowSystem();
		~Win32_WindowSystem();

		void initSystem(std::string m_assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		std::string getName() override;

		IWindow* createWindow(std::string title, WINDOW_MODE windowMode, int width, int height) override;
		void deleteWindow(IWindow* window) override;

	private:
		void registerWindowClass(LPCWSTR className, WNDPROC wndProc);
		void unregisterWindowClass(LPCWSTR className);

	private:
		HINSTANCE hInstance = nullptr;
		LPCWSTR m_fierceWindowClassName = L"FierceWindow";
		std::vector<IWindow*> m_windows;

		ILoggingSystem* m_loggingSystem=nullptr;
		ILogger* m_logger=nullptr;

		IInputSystem* m_inputSystem=nullptr;

	public:
		static std::unordered_map<int, BINDING> m_bindings;
	};

}//end namespace