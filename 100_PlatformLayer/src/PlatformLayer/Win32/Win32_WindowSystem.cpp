#include "Win32_WindowSystem.h"

#include "Win32_Window.h"

#include "src/PlatformLayer/include/LoggingSystem.h"

#include "src/PlatformLayer/include/InputSystem.h"

namespace Fierce {

	std::unordered_map<int, BINDING> Win32_WindowSystem::m_bindings = {
		// Function keys
		{VK_F1, BINDING::KEY_F1},
		{VK_F2, BINDING::KEY_F2},
		{VK_F3, BINDING::KEY_F3},
		{VK_F4, BINDING::KEY_F4},
		{VK_F5, BINDING::KEY_F5},
		{VK_F6, BINDING::KEY_F6},
		{VK_F7, BINDING::KEY_F7},
		{VK_F8, BINDING::KEY_F8},
		{VK_F9, BINDING::KEY_F9},
		{VK_F10, BINDING::KEY_F10},
		{VK_F11, BINDING::KEY_F11},
		{VK_F12, BINDING::KEY_F12},

		// Alphanumeric keys
		{0x41, BINDING::KEY_A}, // A
		{0x42, BINDING::KEY_B}, // B
		{0x43, BINDING::KEY_C}, // C
		{0x44, BINDING::KEY_D}, // D
		{0x45, BINDING::KEY_E}, // E
		{0x46, BINDING::KEY_F}, // F
		{0x47, BINDING::KEY_G}, // G
		{0x48, BINDING::KEY_H}, // H
		{0x49, BINDING::KEY_I}, // I
		{0x4A, BINDING::KEY_J}, // J
		{0x4B, BINDING::KEY_K}, // K
		{0x4C, BINDING::KEY_L}, // L
		{0x4D, BINDING::KEY_M}, // M
		{0x4E, BINDING::KEY_N}, // N
		{0x4F, BINDING::KEY_O}, // O
		{0x50, BINDING::KEY_P}, // P
		{0x51, BINDING::KEY_Q}, // Q
		{0x52, BINDING::KEY_R}, // R
		{0x53, BINDING::KEY_S}, // S
		{0x54, BINDING::KEY_T}, // T
		{0x55, BINDING::KEY_U}, // U
		{0x56, BINDING::KEY_V}, // V
		{0x57, BINDING::KEY_W}, // W
		{0x58, BINDING::KEY_X}, // X
		{0x59, BINDING::KEY_Y}, // Y
		{0x5A, BINDING::KEY_Z}, // Z

		// Numeric keys
		{0x30, BINDING::KEY_0}, // 0
		{0x31, BINDING::KEY_1}, // 1
		{0x32, BINDING::KEY_2}, // 2
		{0x33, BINDING::KEY_3}, // 3
		{0x34, BINDING::KEY_4}, // 4
		{0x35, BINDING::KEY_5}, // 5
		{0x36, BINDING::KEY_6}, // 6
		{0x37, BINDING::KEY_7}, // 7
		{0x38, BINDING::KEY_8}, // 8
		{0x39, BINDING::KEY_9}, // 9

		// Control keys
		{VK_ESCAPE, BINDING::KEY_ESC},
		{VK_TAB, BINDING::KEY_TAB},
		{VK_SHIFT, BINDING::KEY_SHIFT},
		{VK_CONTROL, BINDING::KEY_CTRL},
		{VK_MENU, BINDING::KEY_ALT},
		{VK_RETURN, BINDING::KEY_ENTER},
		{VK_BACK, BINDING::KEY_BACKSPACE},
		{VK_SPACE, BINDING::KEY_SPACE},

		// Arrow keys
		{VK_LEFT, BINDING::KEY_LEFT},
		{VK_UP, BINDING::KEY_UP},
		{VK_RIGHT, BINDING::KEY_RIGHT},
		{VK_DOWN, BINDING::KEY_DOWN},

		// Special keys
		{VK_INSERT, BINDING::KEY_INSERT},
		{VK_DELETE, BINDING::KEY_DELETE},
		{VK_HOME, BINDING::KEY_HOME},
		{VK_END, BINDING::KEY_END},
		{VK_PRIOR, BINDING::KEY_PAGE_UP},
		{VK_NEXT, BINDING::KEY_PAGE_DOWN},

		// Numeric keypad
		{VK_NUMPAD0, BINDING::KEY_NUMPAD0},
		{VK_NUMPAD1, BINDING::KEY_NUMPAD1},
		{VK_NUMPAD2, BINDING::KEY_NUMPAD2},
		{VK_NUMPAD3, BINDING::KEY_NUMPAD3},
		{VK_NUMPAD4, BINDING::KEY_NUMPAD4},
		{VK_NUMPAD5, BINDING::KEY_NUMPAD5},
		{VK_NUMPAD6, BINDING::KEY_NUMPAD6},
		{VK_NUMPAD7, BINDING::KEY_NUMPAD7},
		{VK_NUMPAD8, BINDING::KEY_NUMPAD8},
		{VK_NUMPAD9, BINDING::KEY_NUMPAD9},
		{VK_ADD, BINDING::KEY_NUMPAD_PLUS},
		{VK_SUBTRACT, BINDING::KEY_NUMPAD_MINUS},
		{VK_MULTIPLY, BINDING::KEY_NUMPAD_MULTIPLY},
		{VK_DIVIDE, BINDING::KEY_NUMPAD_DIVIDE},
		{VK_DECIMAL, BINDING::KEY_NUMPAD_DECIMAL}
	};

	LRESULT CALLBACK wndProcFierceWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		InputSystem* inputSystem = static_cast<InputSystem*>(GetProp(hWnd, L"inputSystem"));
		Logger* logger = static_cast<Logger*>(GetProp(hWnd, L"logger"));
		Window* window = static_cast<Window*>(GetProp(hWnd, L"window"));

		short wheelDelta;
		int x,y,deltaX,deltaY;
		UINT bufferSize, error;
		RAWINPUT* raw;

		switch (message) {
			//*** Window ***//
		case WM_CLOSE:
			return 0;
		case WM_SIZE:
			if (window!=nullptr) {
				window->onResize(LOWORD(lParam), HIWORD(lParam));
			}
			return 0;
			//*** Keyboard ***//
		case WM_KEYDOWN:
			inputSystem->getActiveContext()->onKeyDown(Win32_WindowSystem::m_bindings[wParam]);
			return 0;
		case WM_KEYUP:
			inputSystem->getActiveContext()->onKeyUp(Win32_WindowSystem::m_bindings[wParam]);
			return 0;
		case WM_CHAR:
			return 0;
			//*** Mouse ***//
		case WM_LBUTTONDOWN:
			inputSystem->getActiveContext()->onMouseKeyDown( BINDING::MOUSE_BUTTON_LEFT);
			return 0;
		case WM_RBUTTONDOWN:
			inputSystem->getActiveContext()->onMouseKeyDown( BINDING::MOUSE_BUTTON_RIGHT);
			return 0;
		case WM_MBUTTONDOWN:
			inputSystem->getActiveContext()->onMouseKeyDown( BINDING::MOUSE_BUTTON_MIDDLE);
			return 0;
		case WM_LBUTTONUP:
			inputSystem->getActiveContext()->onMouseKeyUp( BINDING::MOUSE_BUTTON_LEFT);
			return 0;
		case WM_RBUTTONUP:
			inputSystem->getActiveContext()->onMouseKeyUp( BINDING::MOUSE_BUTTON_RIGHT);
			return 0;
		case WM_MBUTTONUP:
			inputSystem->getActiveContext()->onMouseKeyUp( BINDING::MOUSE_BUTTON_MIDDLE);
			return 0;
		case WM_MOUSEWHEEL:
			wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			inputSystem->getActiveContext()->onMouseWheelMove( BINDING::MOUSE_WHEEL_MOVE, wheelDelta);
			return 0;
		case WM_MOUSEMOVE:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			inputSystem->getActiveContext()->onMouseMoved(BINDING::MOUSE_MOVE, x,y);
			return 0;
		case WM_INPUT:
			bufferSize = sizeof(RAWINPUT);
			static BYTE buffer[sizeof(RAWINPUT)];
			error=GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &bufferSize, sizeof(RAWINPUTHEADER));
			raw = (RAWINPUT*)buffer;

			if (error == (UINT)-1) {
				return DefWindowProc(hWnd, message, wParam, lParam);
			}

			if (raw->header.dwType == RIM_TYPEMOUSE) {
				RAWMOUSE& mouse = raw->data.mouse;

				//Mouse move
				if (mouse.lLastX != 0 && mouse.lLastY != 0) {
					inputSystem->getActiveContext()->onMouseMoved( BINDING::MOUSE_MOVE, mouse.lLastX, mouse.lLastY);
				}

				//Mouse buttons
				if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {
					inputSystem->getActiveContext()->onMouseKeyDown( BINDING::MOUSE_BUTTON_LEFT);
				}
				if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) {
					inputSystem->getActiveContext()->onMouseKeyUp( BINDING::MOUSE_BUTTON_LEFT);
				}
				if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) {
					inputSystem->getActiveContext()->onMouseKeyDown( BINDING::MOUSE_BUTTON_MIDDLE);
				}
				if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) {
					inputSystem->getActiveContext()->onMouseKeyUp( BINDING::MOUSE_BUTTON_MIDDLE);
				}
				if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) {
					inputSystem->getActiveContext()->onMouseKeyDown( BINDING::MOUSE_BUTTON_RIGHT);
				}
				if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) {
					inputSystem->getActiveContext()->onMouseKeyUp( BINDING::MOUSE_BUTTON_RIGHT);
				}

				//Mouse wheel
				if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
					wheelDelta = (SHORT)mouse.usButtonData;
					inputSystem->getActiveContext()->onMouseWheelMove( BINDING::MOUSE_WHEEL_MOVE, wheelDelta);
				}
			}
			return 0;
			//****************//
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	LRESULT CALLBACK wndProcFierceDummyWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	Win32_WindowSystem::Win32_WindowSystem() {
		
	}

	Win32_WindowSystem::~Win32_WindowSystem() {
		
	}

	void Win32_WindowSystem::initSystem(std::string m_assetDirectory){
		if (m_loggingSystem != nullptr) {
			m_logger = m_loggingSystem->createLogger("WIN", true, "ALL_LOGS");
			m_logger->info("Init window system");
		}
		hInstance = GetModuleHandle(NULL);
		registerWindowClass(m_fierceWindowClassName, wndProcFierceWindow);
	}

	void Win32_WindowSystem::linkSystem(System* system){
		if (dynamic_cast<LoggingSystem*>(system)) {
			m_loggingSystem = (LoggingSystem*)system;
		}
		else if (dynamic_cast<InputSystem*>(system)) {
			m_inputSystem = (InputSystem*)system;
		}
	}

	void Win32_WindowSystem::updateSystem(){
		for (Window* window:m_windows) {
			window->pollEvents();
		}
	}

	void Win32_WindowSystem::cleanUpSystem(){
		unregisterWindowClass(m_fierceWindowClassName);

		if (m_logger != nullptr) {
			m_logger->info("Clean up window system");
			m_loggingSystem->deleteLogger(m_logger);
		}
	}

	Window* Win32_WindowSystem::createWindow(std::string title, Window::WINDOW_MODE windowMode, int width, int height){
		Win32_Window* window= new Win32_Window(m_logger,m_fierceWindowClassName,title,windowMode,width,height);
		SetProp(window->getHandle(), L"inputSystem", m_inputSystem);
		SetProp(window->getHandle(), L"logger", m_logger);
		SetProp(window->getHandle(), L"window", window);
		m_windows.push_back(window);
		return window;
	}

	void Win32_WindowSystem::deleteWindow(Window* window){
		auto it = std::find(m_windows.begin(), m_windows.end(), window);
		if (it != m_windows.end()) {
			m_windows.erase(it);
			delete window;
		}
		else {
			m_logger->error("Window could not be deleted.");
		}
	}

	void Win32_WindowSystem::registerWindowClass(LPCWSTR className, WNDPROC wndProc) {
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

	void Win32_WindowSystem::unregisterWindowClass(LPCWSTR className) {
		if (!UnregisterClass(className, hInstance)) {
			m_logger->error("Failed to unregister window class.");
		}
	}

}//end namespace