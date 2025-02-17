#pragma once

#include <Windows.h>
#include "src/FierceStrings.h"

namespace Fierce{

	class Logger;

	class Window {
	public:
		enum WINDOW_MODE {
			WINDOWED, FULLSCREEN
		};

	public:
		Window(Logger* logger,LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		~Window();

		void pollEvents();
		void show();

		HWND getHandle() { return m_windowHandle; }

		int getWidth() { return m_width; }
		int getHeight() { return m_height; }

		void onResize(int width,int height);

	private:
		void createWindow(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		void destroyWindow();

	public:
		void activateRawInput();
		void deactivateRawInput();

	private:
		HWND m_windowHandle = nullptr;
		bool m_isFullscreen = false;
		int m_width;
		int m_height;

		Logger* m_logger;
	};

}//end namespace