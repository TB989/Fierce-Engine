#include "FierceWindow.h"

#include "Logging.h"

#include <strsafe.h>

FierceWindow::FierceWindow(LPCWSTR className, LPCWSTR title, WINDOW_MODE mode, int width, int height, bool dummy) {
	m_width = width;
	m_height = height;
	CHECK_FIERCE(createWindow(className, title, mode, width, height, dummy), "Failed to create window.");
}

FierceWindow::~FierceWindow() {
	CHECK_FIERCE(destroyWindow(), "Failed to destroy window.");
}

WINDOW_ERROR FierceWindow::createWindow(LPCWSTR className, LPCWSTR title, WINDOW_MODE mode, int width, int height, bool dummy) {
	DWORD style = 0;
	DWORD exStyle = WS_EX_APPWINDOW;

	RECT r = RECT();
	r.left = 0;
	r.top = 0;

	if (mode == WINDOWED || dummy) {
		style = WS_OVERLAPPEDWINDOW;
		r.right = width;
		r.bottom = height;
	}
	else if (mode == FULLSCREEN) {
		style = WS_POPUP;
		r.right = GetSystemMetrics(SM_CXSCREEN);
		r.bottom = GetSystemMetrics(SM_CYSCREEN);
		m_width= GetSystemMetrics(SM_CXSCREEN);
		m_height= GetSystemMetrics(SM_CYSCREEN);
	}

	if (!AdjustWindowRectEx(&r, style, FALSE, exStyle)) {
		return FE_WINDOW_ERROR;
	}

	windowHandle = CreateWindowEx(
		exStyle,
		className,
		title,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		r.right - r.left, r.bottom - r.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (!windowHandle) {
		return FE_WINDOW_ERROR;
	}

	return FE_NO_ERROR;
}

void FierceWindow::registerForRawInput(){
	RAWINPUTDEVICE rawInputDevice;
	rawInputDevice.usUsagePage = 0x01;
	rawInputDevice.usUsage = 0x02;
	rawInputDevice.dwFlags = 0;
	rawInputDevice.hwndTarget = windowHandle;
	RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE));
}

void FierceWindow::clipCursor(){
	RECT rc;
	GetClientRect(windowHandle, &rc);
	POINT pt = { rc.left, rc.top };
	POINT pt2 = { rc.right, rc.bottom };
	ClientToScreen(windowHandle, &pt);
	ClientToScreen(windowHandle, &pt2);
	SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
	ClipCursor(&rc);
}

WINDOW_ERROR FierceWindow::destroyWindow() {
	if (!DestroyWindow(windowHandle)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

void FierceWindow::pollEvents() {
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void FierceWindow::show() {
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
}