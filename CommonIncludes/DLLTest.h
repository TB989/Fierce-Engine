#pragma once

typedef void (* PFNTESTFUNCPROC)();
extern PFNTESTFUNCPROC testFunc;

typedef bool (*PFN_INIT_RENDERER_PROC)(HWND dummyWindowHandle,HWND windowHandle);
extern PFNTESTFUNCPROC initRenderer;