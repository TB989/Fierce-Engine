#include "Window.h"

#include "src/LoggingSystem.h"

namespace Fierce {

	Window::Window(Logger* logger, LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height) {
		m_logger = logger;
		createWindow(className, title, windowMode, width, height);
	}

	Window::~Window() {
		destroyWindow();
	}

	void Window::createWindow(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height) {
		std::wstring tit(title.begin(), title.end());

		DWORD style = 0;
		DWORD exStyle = WS_EX_APPWINDOW;

		RECT r = RECT();
		r.left = 0;
		r.top = 0;

		if (windowMode == WINDOWED) {
			style = WS_OVERLAPPEDWINDOW;
			m_width = width;
			m_height = height;
			r.right = width;
			r.bottom = height;
		}
		else if (windowMode == FULLSCREEN) {
			style = WS_POPUP;
			m_width= GetSystemMetrics(SM_CXSCREEN);
			m_height= GetSystemMetrics(SM_CYSCREEN);
			r.right = GetSystemMetrics(SM_CXSCREEN);
			r.bottom = GetSystemMetrics(SM_CYSCREEN);
		}

		if (!AdjustWindowRectEx(&r, style, FALSE, exStyle)) {
			m_logger->error("Failed to adjust window rectangle.");
		}

		m_windowHandle = CreateWindowEx(
			exStyle,
			className,
			tit.c_str(),
			style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			r.right - r.left, r.bottom - r.top,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);

		if (!m_windowHandle) {
			m_logger->error("Failed to create window.");
		}
	}

	void Window::destroyWindow() {
		if (!DestroyWindow(m_windowHandle)) {
			m_logger->error("Failed to destroy window.");
		}
	}

	void Window::pollEvents() {
		MSG msg;
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	void Window::show() {
		ShowWindow(m_windowHandle, SW_SHOW);
		UpdateWindow(m_windowHandle);
	}

}//end namespace