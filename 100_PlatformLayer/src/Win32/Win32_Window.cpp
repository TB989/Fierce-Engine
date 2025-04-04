#include "Win32_Window.h"

#include "src/Win32/Win32_Logger.h"

namespace Fierce {

	Win32_Window::Win32_Window(Logger* logger, LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height) :Window(title,windowMode,width,height){
		m_logger = logger;
		createWindow(className, title, windowMode, width, height);
	}

	Win32_Window::~Win32_Window() {
		destroyWindow();
	}

	void Win32_Window::createWindow(LPCWSTR className, std::string title, WINDOW_MODE windowMode, int width, int height) {
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
			m_isFullscreen = true;
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

		activateRawInput();
	}

	void Win32_Window::destroyWindow() {
		if (!DestroyWindow(m_windowHandle)) {
			m_logger->error("Failed to destroy window.");
		}
	}

	void Win32_Window::activateRawInput(){
		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;  // Generic Desktop Controls
		rid.usUsage = 0x02;      // Mouse
		rid.dwFlags = RIDEV_NOLEGACY; // Capture input even when not in focus
		rid.hwndTarget = m_windowHandle;

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
			m_logger->error("Failed to register raw input device.");
		}
	}

	void Win32_Window::deactivateRawInput(){
		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;  // Generic Desktop Controls
		rid.usUsage = 0x02;      // Mouse
		rid.dwFlags = RIDEV_REMOVE; // Capture input even when not in focus
		rid.hwndTarget = NULL;

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
			m_logger->error("Failed to deregister raw input device.");
		}
	}

	void Win32_Window::onResize(int width, int height){
		if (!m_isFullscreen) {
			m_width = width;
			m_height = height;
		}
	}

	void Win32_Window::pollEvents() {
		MSG msg;
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	void Win32_Window::show() {
		ShowWindow(m_windowHandle, SW_SHOW);
		UpdateWindow(m_windowHandle);
	}

}//end namespace