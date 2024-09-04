#include "WindowSystem.h"

namespace Fierce {

	LRESULT CALLBACK wndProcFierceWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		WindowSystem* windowSystem = static_cast<WindowSystem*>(GetProp(hWnd, L"windowSystem"));

		switch (message) {
			//*** Window ***//
		case WM_CLOSE:
			if (windowSystem->m_onWindowClosed != nullptr) {
				windowSystem->m_onWindowClosed();
			}
			return 0;
		case WM_SIZE:
			return 0;
			//*** Keyboard ***//
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				if (windowSystem->m_onWindowClosed != nullptr) {
					windowSystem->m_onWindowClosed();
				}
			}
			return 0;
		case WM_KEYUP:
			return 0;
		case WM_CHAR:
			return 0;
			//*** Mouse ***//
		case WM_LBUTTONDOWN:
			return 0;
		case WM_RBUTTONDOWN:
			return 0;
		case WM_MBUTTONDOWN:
			return 0;
		case WM_LBUTTONUP:
			return 0;
		case WM_RBUTTONUP:
			return 0;
		case WM_MBUTTONUP:
			return 0;
		case WM_MOUSEMOVE:
			return 0;
		case WM_MOUSEWHEEL:
			return 0;
			//****************//
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	LRESULT CALLBACK wndProcFierceDummyWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	WindowSystem::WindowSystem() {
		m_logger = new Logger("WIN", true, "ALL_LOGS");
		hInstance = GetModuleHandle(NULL);
		registerWindowClass(m_fierceWindowClassName, wndProcFierceWindow);
	}

	WindowSystem::~WindowSystem() {
		unregisterWindowClass(m_fierceWindowClassName);
		delete m_logger;
	}

	Window* WindowSystem::createWindow(std::string title, Window::WINDOW_MODE windowMode, int width, int height){
		Window* window= new Window(m_fierceWindowClassName,title,windowMode,width,height);
		SetProp(window->getHandle(), L"windowSystem", this);
		m_windows.push_back(window);
		return window;
	}

	void WindowSystem::deleteWindow(Window* window){
		auto it = std::find(m_windows.begin(), m_windows.end(), window);
		if (it != m_windows.end()) {
			m_windows.erase(it);
			delete window;
		}
		else {
			m_logger->error("Window could not be deleted.");
		}
	}

	void WindowSystem::registerWindowClass(LPCWSTR className, WNDPROC wndProc) {
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = className;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc)) {
			m_logger->error("Failed to register window class.");
		}
	}

	void WindowSystem::unregisterWindowClass(LPCWSTR className) {
		if (!UnregisterClass(className, hInstance)) {
			m_logger->error("Failed to unregister window class.");
		}
	}

}//end namespace