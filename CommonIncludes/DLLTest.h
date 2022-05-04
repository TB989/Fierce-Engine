#pragma once

typedef bool (*PFN_INIT_RENDERER_PROC)(HWND dummyWindowHandle,HWND windowHandle);
extern PFN_INIT_RENDERER_PROC initRenderer;

typedef bool (*PFN_RENDER_PROC)();
extern PFN_RENDER_PROC render;

typedef bool (*PFN_CLEAN_UP_RENDERER_PROC)();
extern PFN_CLEAN_UP_RENDERER_PROC cleanUpRenderer;