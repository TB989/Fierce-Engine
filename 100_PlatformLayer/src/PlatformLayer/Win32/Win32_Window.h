#pragma once

#include "Windows.h"

#include "src/systems/IWindowSystem.h"

namespace Fierce{

	class ILogger;

	class Win32_Window :public IWindow{
	public:
		Win32_Window(ILogger* logger,LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		~Win32_Window();

		void pollEvents() override;
		void show() override;
		void onResize(int width, int height) override;
		void onClose() override;
		bool isClosing() override;

		std::string getTitle() override;
		bool isFullcreen() override;
		int getWidth() override;
		int getHeight() override;

		HWND getHandle() { return m_windowHandle; }

	private:
		void createWindow(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height);
		void destroyWindow();

	public:
		void activateRawInput() override;
		void deactivateRawInput() override;

	private:
		HWND m_windowHandle = nullptr;

		ILogger* m_logger;

		std::string m_title = "";
		bool m_isFullscreen = false;
		bool m_isClosing = false;
		int m_width = -1;
		int m_height = -1;
	};

}//end namespace