#pragma once

#include "windows.h"
#include <cstdint>
#include <string>

#ifdef DLL_EXPORT
	#define RENDERER_API extern "C" __declspec(dllexport)
#endif // DLL_EXPORT

#ifdef DLL_IMPORT
	typedef bool (*PFN_INIT_RENDERER_PROC)(HWND dummyWindowHandle, HWND windowHandle);
	typedef bool (*PFN_RENDER_PROC)();
	typedef bool (*PFN_CLEAN_UP_RENDERER_PROC)();

	extern PFN_INIT_RENDERER_PROC initRenderer;
	extern PFN_RENDER_PROC render;
	extern PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer;
#endif // DLL_IMPORT