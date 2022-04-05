#pragma once

typedef void (* PFNTESTFUNCPROC)();
extern PFNTESTFUNCPROC testFunc;

typedef bool (*PFN_INIT_RENDERER_PROC)();
extern PFNTESTFUNCPROC initRenderer;