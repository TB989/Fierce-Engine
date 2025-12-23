#pragma once

#include "../systems/IWindowSystem.h"
#include <string>

namespace Fierce {

	struct EngineSettings {
		//Window
		WINDOW_MODE windowMode = WINDOW_MODE::WINDOWED;
		int width = 800;
		int height = 600;

		//Asset path
		std::string assetPath = "";
	};

}//end namespace
