#pragma once

#include "src/WindowSystem.h"
#include "src/FierceStrings.h"
#include <map>

namespace Fierce {

	struct EngineSettings {
		//Window
		Window::WINDOW_MODE windowMode = Window::WINDOW_MODE::WINDOWED;
		int width = 800;
		int height = 600;

		void parse(std::map<std::string, std::string> settings) {
			std::map<std::string, std::string>::iterator it = settings.begin();
			while (it != settings.end()) {
				std::string key = it->first;
				std::string value = it->second;
				if (key == "windowMode" || key == "WINDOW_MODE") {
					if (value == "windowed" || value == "WINDOWED") {
						windowMode = Window::WINDOW_MODE::WINDOWED;
					}
					if (value == "fullscreen" || value == "FULLSCREEN") {
						windowMode = Window::WINDOW_MODE::FULLSCREEN;
					}
				}
				if (key == "width" || key == "WIDTH") {
					width = std::stoi(value);
				}
				if (key == "height" || key == "HEIGHT") {
					height = std::stoi(value);
				}
				it++;
			}
		}
	};

}//end namespace