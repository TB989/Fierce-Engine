#pragma once

#include "Windows.h"

#include "src/include/WindowSystem.h"

namespace Fierce{

	class Logger;

	class Win32_Window :public Window{
	public:
		Win32_Window(Logger* logger,LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		~Win32_Window();

		void pollEvents() override;
		void show() override;
		void onResize(int width, int height) override;

		HWND getHandle() { return m_windowHandle; }

	private:
		void createWindow(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		void destroyWindow();

	public:
		void activateRawInput();
		void deactivateRawInput();

	private:
		HWND m_windowHandle = nullptr;

		Logger* m_logger;
	};

}//end namespace