#include "WindowSystem.h"

#include "src/LoggingSystem.h"

namespace Fierce {

	std::unordered_map<int, InputSystem::BINDING> WindowSystem::m_bindings = {
		// Function keys
		{VK_F1, InputSystem::BINDING::KEY_F1},
		{VK_F2, InputSystem::BINDING::KEY_F2},
		{VK_F3, InputSystem::BINDING::KEY_F3},
		{VK_F4, InputSystem::BINDING::KEY_F4},
		{VK_F5, InputSystem::BINDING::KEY_F5},
		{VK_F6, InputSystem::BINDING::KEY_F6},
		{VK_F7, InputSystem::BINDING::KEY_F7},
		{VK_F8, InputSystem::BINDING::KEY_F8},
		{VK_F9, InputSystem::BINDING::KEY_F9},
		{VK_F10, InputSystem::BINDING::KEY_F10},
		{VK_F11, InputSystem::BINDING::KEY_F11},
		{VK_F12, InputSystem::BINDING::KEY_F12},

		// Alphanumeric keys
		{0x41, InputSystem::BINDING::KEY_A}, // A
		{0x42, InputSystem::BINDING::KEY_B}, // B
		{0x43, InputSystem::BINDING::KEY_C}, // C
		{0x44, InputSystem::BINDING::KEY_D}, // D
		{0x45, InputSystem::BINDING::KEY_E}, // E
		{0x46, InputSystem::BINDING::KEY_F}, // F
		{0x47, InputSystem::BINDING::KEY_G}, // G
		{0x48, InputSystem::BINDING::KEY_H}, // H
		{0x49, InputSystem::BINDING::KEY_I}, // I
		{0x4A, InputSystem::BINDING::KEY_J}, // J
		{0x4B, InputSystem::BINDING::KEY_K}, // K
		{0x4C, InputSystem::BINDING::KEY_L}, // L
		{0x4D, InputSystem::BINDING::KEY_M}, // M
		{0x4E, InputSystem::BINDING::KEY_N}, // N
		{0x4F, InputSystem::BINDING::KEY_O}, // O
		{0x50, InputSystem::BINDING::KEY_P}, // P
		{0x51, InputSystem::BINDING::KEY_Q}, // Q
		{0x52, InputSystem::BINDING::KEY_R}, // R
		{0x53, InputSystem::BINDING::KEY_S}, // S
		{0x54, InputSystem::BINDING::KEY_T}, // T
		{0x55, InputSystem::BINDING::KEY_U}, // U
		{0x56, InputSystem::BINDING::KEY_V}, // V
		{0x57, InputSystem::BINDING::KEY_W}, // W
		{0x58, InputSystem::BINDING::KEY_X}, // X
		{0x59, InputSystem::BINDING::KEY_Y}, // Y
		{0x5A, InputSystem::BINDING::KEY_Z}, // Z

		// Numeric keys
		{0x30, InputSystem::BINDING::KEY_0}, // 0
		{0x31, InputSystem::BINDING::KEY_1}, // 1
		{0x32, InputSystem::BINDING::KEY_2}, // 2
		{0x33, InputSystem::BINDING::KEY_3}, // 3
		{0x34, InputSystem::BINDING::KEY_4}, // 4
		{0x35, InputSystem::BINDING::KEY_5}, // 5
		{0x36, InputSystem::BINDING::KEY_6}, // 6
		{0x37, InputSystem::BINDING::KEY_7}, // 7
		{0x38, InputSystem::BINDING::KEY_8}, // 8
		{0x39, InputSystem::BINDING::KEY_9}, // 9

		// Control keys
		{VK_ESCAPE, InputSystem::BINDING::KEY_ESC},
		{VK_TAB, InputSystem::BINDING::KEY_TAB},
		{VK_SHIFT, InputSystem::BINDING::KEY_SHIFT},
		{VK_CONTROL, InputSystem::BINDING::KEY_CTRL},
		{VK_MENU, InputSystem::BINDING::KEY_ALT},
		{VK_RETURN, InputSystem::BINDING::KEY_ENTER},
		{VK_BACK, InputSystem::BINDING::KEY_BACKSPACE},
		{VK_SPACE, InputSystem::BINDING::KEY_SPACE},

		// Arrow keys
		{VK_LEFT, InputSystem::BINDING::KEY_LEFT},
		{VK_UP, InputSystem::BINDING::KEY_UP},
		{VK_RIGHT, InputSystem::BINDING::KEY_RIGHT},
		{VK_DOWN, InputSystem::BINDING::KEY_DOWN},

		// Special keys
		{VK_INSERT, InputSystem::BINDING::KEY_INSERT},
		{VK_DELETE, InputSystem::BINDING::KEY_DELETE},
		{VK_HOME, InputSystem::BINDING::KEY_HOME},
		{VK_END, InputSystem::BINDING::KEY_END},
		{VK_PRIOR, InputSystem::BINDING::KEY_PAGE_UP},
		{VK_NEXT, InputSystem::BINDING::KEY_PAGE_DOWN},

		// Numeric keypad
		{VK_NUMPAD0, InputSystem::BINDING::KEY_NUMPAD0},
		{VK_NUMPAD1, InputSystem::BINDING::KEY_NUMPAD1},
		{VK_NUMPAD2, InputSystem::BINDING::KEY_NUMPAD2},
		{VK_NUMPAD3, InputSystem::BINDING::KEY_NUMPAD3},
		{VK_NUMPAD4, InputSystem::BINDING::KEY_NUMPAD4},
		{VK_NUMPAD5, InputSystem::BINDING::KEY_NUMPAD5},
		{VK_NUMPAD6, InputSystem::BINDING::KEY_NUMPAD6},
		{VK_NUMPAD7, InputSystem::BINDING::KEY_NUMPAD7},
		{VK_NUMPAD8, InputSystem::BINDING::KEY_NUMPAD8},
		{VK_NUMPAD9, InputSystem::BINDING::KEY_NUMPAD9},
		{VK_ADD, InputSystem::BINDING::KEY_NUMPAD_PLUS},
		{VK_SUBTRACT, InputSystem::BINDING::KEY_NUMPAD_MINUS},
		{VK_MULTIPLY, InputSystem::BINDING::KEY_NUMPAD_MULTIPLY},
		{VK_DIVIDE, InputSystem::BINDING::KEY_NUMPAD_DIVIDE},
		{VK_DECIMAL, InputSystem::BINDING::KEY_NUMPAD_DECIMAL}
	};

	LRESULT CALLBACK wndProcFierceWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		InputSystem* inputSystem = static_cast<InputSystem*>(GetProp(hWnd, L"inputSystem"));
		Logger* logger = static_cast<Logger*>(GetProp(hWnd, L"logger"));

		short wheelDelta;
		int x,y;

		switch (message) {
			//*** Window ***//
		case WM_CLOSE:
			return 0;
		case WM_SIZE:
			return 0;
			//*** Keyboard ***//
		case WM_KEYDOWN:
			inputSystem->onKeyDown(WindowSystem::m_bindings[wParam]);
			return 0;
		case WM_KEYUP:
			inputSystem->onKeyUp(WindowSystem::m_bindings[wParam]);
			return 0;
		case WM_CHAR:
			return 0;
			//*** Mouse ***//
		case WM_LBUTTONDOWN:
			inputSystem->onMouseKeyDown(InputSystem::BINDING::MOUSE_BUTTON_LEFT);
			return 0;
		case WM_RBUTTONDOWN:
			inputSystem->onMouseKeyDown(InputSystem::BINDING::MOUSE_BUTTON_RIGHT);
			return 0;
		case WM_MBUTTONDOWN:
			inputSystem->onMouseKeyDown(InputSystem::BINDING::MOUSE_BUTTON_MIDDLE);
			return 0;
		case WM_LBUTTONUP:
			inputSystem->onMouseKeyUp(InputSystem::BINDING::MOUSE_BUTTON_LEFT);
			return 0;
		case WM_RBUTTONUP:
			inputSystem->onMouseKeyUp(InputSystem::BINDING::MOUSE_BUTTON_RIGHT);
			return 0;
		case WM_MBUTTONUP:
			inputSystem->onMouseKeyUp(InputSystem::BINDING::MOUSE_BUTTON_MIDDLE);
			return 0;
		case WM_MOUSEMOVE:
			x = LOWORD(lParam);  // Get the x-coordinate
			y = HIWORD(lParam);  // Get the y-coordinate
			inputSystem->onMouseMoveX(InputSystem::BINDING::MOUSE_X_AXIS,x);
			inputSystem->onMouseMoveY(InputSystem::BINDING::MOUSE_Y_AXIS,y);
			return 0;
		case WM_MOUSEWHEEL:
			wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			inputSystem->onMouseWheelMove(InputSystem::BINDING::MOUSE_WHEEL_MOVE, wheelDelta);
			return 0;
			//****************//
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	LRESULT CALLBACK wndProcFierceDummyWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	WindowSystem::WindowSystem(LoggingSystem* loggingSystem, InputSystem* inputSystem) {
		m_loggingSystem = loggingSystem;
		m_inputSystem = inputSystem;
	}

	WindowSystem::~WindowSystem() {
		m_loggingSystem->deleteLogger(m_logger);
	}

	void WindowSystem::initSystem(){
		m_logger = m_loggingSystem->createLogger("WIN", true, "ALL_LOGS");
		hInstance = GetModuleHandle(NULL);
		registerWindowClass(m_fierceWindowClassName, wndProcFierceWindow);

		m_bindings.insert({VK_ESCAPE,InputSystem::BINDING::KEY_ESC});
	}

	void WindowSystem::updateSystem(){
		for (Window* window:m_windows) {
			window->pollEvents();
		}
	}

	void WindowSystem::cleanUpSystem(){
		unregisterWindowClass(m_fierceWindowClassName);
	}

	Window* WindowSystem::createWindow(std::string title, Window::WINDOW_MODE windowMode, int width, int height){
		Window* window= new Window(m_logger,m_fierceWindowClassName,title,windowMode,width,height);
		SetProp(window->getHandle(), L"inputSystem", m_inputSystem);
		SetProp(window->getHandle(), L"logger", m_logger);
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