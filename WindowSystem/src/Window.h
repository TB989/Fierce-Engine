#pragma once

#include <Windows.h>
#include "src/Logger.h"
#include "src/FierceStrings.h"

namespace Fierce{

	class Window {
	public:
		enum WINDOW_MODE {
			WINDOWED, FULLSCREEN
		};

	public:
		Window(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		~Window();

		void pollEvents();
		void show();

		HWND getHandle() { return m_windowHandle; }

	private:
		void createWindow(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		void destroyWindow();

	private:
		HWND m_windowHandle = nullptr;
		int m_width;
		int m_height;

		Logger* m_logger;
	};

}//end namespace