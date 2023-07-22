#include "WindowSystem.h"

#include "Logging.h"

#include <strsafe.h>

LRESULT CALLBACK wndProcFierceWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	InputSystem* inputSystem = static_cast<InputSystem*>(GetProp(hWnd, L"inputSystem"));
	WindowSystem* windowSystem = static_cast<WindowSystem*>(GetProp(hWnd, L"windowSystem"));
	MAPPING mapping=MAPPING::NONE;

	RAWINPUT* raw;
	LPBYTE lpb;

	int dx=0;
	int dy = 0;

	switch (message) {
	//*** Window ***//
	case WM_CLOSE:
		return 0;

	//*** Keyboard ***//
	case WM_KEYDOWN:
		mapping = windowSystem->getMapping(wParam);
		if (mapping != MAPPING::NONE)inputSystem->fireAction(mapping,1.0f);
		return 0;
	/**case WM_KEYUP:
		mapping = windowSystem->getMapping(wParam);
		if (mapping != MAPPING::NONE)inputSystem->fireAction(mapping, -1.0f);
		return 0;
	case WM_CHAR:
		mapping = windowSystem->getMapping(wParam);
		if (mapping != MAPPING::NONE)inputSystem->fireAction(mapping, 0.0f);
		return 0;*/

	//*** Mouse ***//
	case WM_LBUTTONDOWN:
		inputSystem->fireAction(MAPPING::MOUSE_BUTTON_LEFT, 1.0f);
		return 0;
	case WM_RBUTTONDOWN:
		inputSystem->fireAction(MAPPING::MOUSE_BUTTON_RIGHT, 1.0f);
		return 0;
	case WM_MBUTTONDOWN:
		inputSystem->fireAction(MAPPING::MOUSE_BUTTON_MIDDLE, 1.0f);
		return 0;
	/**case WM_LBUTTONUP:
		inputSystem->fireAction(MAPPING::MOUSE_BUTTON_LEFT, 0.0f);
		return 0;
	case WM_RBUTTONUP:
		inputSystem->fireAction(MAPPING::MOUSE_BUTTON_RIGHT, 0.0f);
		return 0;
	case WM_MBUTTONUP:
		inputSystem->fireAction(MAPPING::MOUSE_BUTTON_MIDDLE, 0.0f);
		return 0;*/
	case WM_MOUSEMOVE:
		if (windowSystem->first) {
			windowSystem->m_x_alt = GET_X_LPARAM(lParam);
			windowSystem->m_y_alt = GET_Y_LPARAM(lParam);
			windowSystem->first = false;
		}

		dx = windowSystem->m_x_alt - GET_X_LPARAM(lParam);
		dy = windowSystem->m_y_alt - GET_Y_LPARAM(lParam);
		windowSystem->m_x_alt = GET_X_LPARAM(lParam);
		windowSystem->m_y_alt = GET_Y_LPARAM(lParam);

		inputSystem->fireAction(MAPPING::MOUSE_AXIS_LR, dx);
		inputSystem->fireAction(MAPPING::MOUSE_AXIS_UD, dy);
		return 0;
	case WM_MOUSEWHEEL:
		inputSystem->fireAction(MAPPING::MOUSE_WHEEL, GET_WHEEL_DELTA_WPARAM(wParam));
		return 0;

	//*** Raw Input ***//
	case WM_INPUT:
		UINT dwSize;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
		lpb = new BYTE[dwSize];
		if (lpb == NULL)
		{
			return 0;
		}

		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));
		raw = (RAWINPUT*)lpb;

		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			//LOGGER->info("Raw input: ");
			//LOGGER->info("Us flags: %d", raw->data.mouse.usFlags);
			//LOGGER->info("Us button flags: %d", raw->data.mouse.usButtonFlags);
			//LOGGER->info("Us button data: %d", raw->data.mouse.usButtonData);
			//LOGGER->info("Last x: %d", raw->data.mouse.lLastX);
			//LOGGER->info("Last y: %d", raw->data.mouse.lLastY);
			//LOGGER->info("Extra: %d", raw->data.mouse.ulExtraInformation);
			/**HRESULT hResult = StringCchPrintf(szTempOutput, STRSAFE_MAX_CCH,
				TEXT("Mouse: usFlags=%04x ulButtons=%04x usButtonFlags=%04x usButtonData=%04x ulRawButtons=%04x lLastX=%04x lLastY=%04x ulExtraInformation=%04x\r\n"),
				raw->data.mouse.usFlags,
				raw->data.mouse.ulButtons,
				raw->data.mouse.usButtonFlags,
				raw->data.mouse.usButtonData,
				raw->data.mouse.ulRawButtons,
				raw->data.mouse.lLastX,
				raw->data.mouse.lLastY,
				raw->data.mouse.ulExtraInformation);

			if (FAILED(hResult))
			{
				// TODO: write error handler
			}
			OutputDebugString(szTempOutput);*/
		}

		delete[] lpb;
		return 0;
		//*****************//
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

LRESULT CALLBACK wndProcFierceDummyWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

WindowSystem::WindowSystem(InputSystem* inputSystem) {
	m_inputSystem = inputSystem;

	mappings['A'] = MAPPING::KEY_A;
	mappings['a'] = MAPPING::KEY_A;
	mappings['B'] = MAPPING::KEY_B;
	mappings['b'] = MAPPING::KEY_B;
	mappings['C'] = MAPPING::KEY_C;
	mappings['c'] = MAPPING::KEY_C;
	mappings['D'] = MAPPING::KEY_D;
	mappings['d'] = MAPPING::KEY_D;
	mappings['E'] = MAPPING::KEY_E;
	mappings['e'] = MAPPING::KEY_E;
	mappings['F'] = MAPPING::KEY_F;
	mappings['f'] = MAPPING::KEY_F;
	mappings['G'] = MAPPING::KEY_G;
	mappings['g'] = MAPPING::KEY_G;
	mappings['H'] = MAPPING::KEY_H;
	mappings['h'] = MAPPING::KEY_H;
	mappings['I'] = MAPPING::KEY_I;
	mappings['i'] = MAPPING::KEY_I;
	mappings['J'] = MAPPING::KEY_J;
	mappings['j'] = MAPPING::KEY_J;
	mappings['K'] = MAPPING::KEY_K;
	mappings['k'] = MAPPING::KEY_K;
	mappings['L'] = MAPPING::KEY_L;
	mappings['l'] = MAPPING::KEY_L;
	mappings['M'] = MAPPING::KEY_M;
	mappings['m'] = MAPPING::KEY_M;
	mappings['N'] = MAPPING::KEY_N;
	mappings['n'] = MAPPING::KEY_N;
	mappings['O'] = MAPPING::KEY_O;
	mappings['o'] = MAPPING::KEY_O;
	mappings['P'] = MAPPING::KEY_P;
	mappings['p'] = MAPPING::KEY_P;
	mappings['Q'] = MAPPING::KEY_Q;
	mappings['q'] = MAPPING::KEY_Q;
	mappings['R'] = MAPPING::KEY_R;
	mappings['r'] = MAPPING::KEY_R;
	mappings['S'] = MAPPING::KEY_S;
	mappings['s'] = MAPPING::KEY_S;
	mappings['T'] = MAPPING::KEY_T;
	mappings['t'] = MAPPING::KEY_T;
	mappings['U'] = MAPPING::KEY_U;
	mappings['u'] = MAPPING::KEY_U;
	mappings['V'] = MAPPING::KEY_V;
	mappings['v'] = MAPPING::KEY_V;
	mappings['W'] = MAPPING::KEY_W;
	mappings['w'] = MAPPING::KEY_W;
	mappings['X'] = MAPPING::KEY_X;
	mappings['x'] = MAPPING::KEY_X;
	mappings['Y'] = MAPPING::KEY_Y;
	mappings['y'] = MAPPING::KEY_Y;
	mappings['Z'] = MAPPING::KEY_Z;
	mappings['z'] = MAPPING::KEY_Z;

	mappings[VK_ESCAPE] = MAPPING::KEY_ESC;
	mappings[VK_F1] = MAPPING::KEY_F1;
	mappings[VK_F2] = MAPPING::KEY_F2;
	mappings[VK_F3] = MAPPING::KEY_F3;
	mappings[VK_F4] = MAPPING::KEY_F4;
	mappings[VK_F5] = MAPPING::KEY_F5;
	mappings[VK_F6] = MAPPING::KEY_F6;
	mappings[VK_F7] = MAPPING::KEY_F7;
	mappings[VK_F8] = MAPPING::KEY_F8;
	mappings[VK_F9] = MAPPING::KEY_F9;
	mappings[VK_F10] = MAPPING::KEY_F10;
	mappings[VK_F11] = MAPPING::KEY_F11;
	mappings[VK_F12] = MAPPING::KEY_F12;

	mappings[VK_TAB] = MAPPING::KEY_TAB;
	mappings[VK_RETURN] = MAPPING::KEY_ENTER;
	mappings[VK_SPACE] = MAPPING::KEY_SPACE;
	mappings[VK_SHIFT] = MAPPING::KEY_SHIFT;

	hInstance = GetModuleHandle(NULL);

	CHECK_FIERCE(registerWindowClass(fierceWindowClassName, wndProcFierceWindow), "Failed to register window class for fierce window.");
	CHECK_FIERCE(registerWindowClass(fierceDummyWindowClassName, wndProcFierceDummyWindow), "Failed to register window class for fierce dummy window.");
}

WindowSystem::~WindowSystem() {
	delete m_dummyWindow;
	delete m_window;
	CHECK_FIERCE(unregisterWindowClass(fierceWindowClassName), "Failed to unregister window class for fierce window.");
	CHECK_FIERCE(unregisterWindowClass(fierceDummyWindowClassName), "Failed to unregister window class for fierce dummy window.");
}

WINDOW_ERROR WindowSystem::registerWindowClass(LPCWSTR className, WNDPROC wndProc) {
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
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

WINDOW_ERROR WindowSystem::unregisterWindowClass(LPCWSTR className) {
	if (!UnregisterClass(className, hInstance)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

void WindowSystem::createWindow(WINDOW_MODE mode, int width, int height){
	m_window = new FierceWindow(fierceWindowClassName, L"FierceWindow", mode, width, height, false);
	SetProp(m_window->getHandle(), L"inputSystem", m_inputSystem);
	SetProp(m_window->getHandle(), L"windowSystem", this);
}

void WindowSystem::createDummyWindow(WINDOW_MODE mode, int width, int height){
	m_dummyWindow = new FierceWindow(fierceDummyWindowClassName, L"FierceDummyWindow", mode, width, height, true);
}