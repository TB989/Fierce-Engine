#pragma once

#include "src/PlatformLayer/include/WindowSystem.h"
#include <string>

namespace Fierce {

	struct EngineSettings {
		//Window
		Window::WINDOW_MODE windowMode = Window::WINDOW_MODE::WINDOWED;
		int width = 800;
		int height = 600;

		//Asset path
		std::string assetPath = "";
	};

}//end namespace
