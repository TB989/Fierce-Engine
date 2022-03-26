#pragma once

#ifdef DLL_EXPORT
	#define RENDERER_API extern "C" __declspec(dllexport)
#endif // DLL_EXPORT