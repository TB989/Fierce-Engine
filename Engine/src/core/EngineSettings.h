#pragma once

#include "WindowSystem.h"
#include "src/Common.h"

enum API {
	VULKAN,
	OPEN_GL,
	DIRECT_X
};

struct EngineSettings {
	//Window
	WINDOW_MODE windowMode = WINDOWED;
	int width = 800;
	int height = 600;

	//Graphics API
	API api = VULKAN;

	void parse(std::map<std::string, std::string> settings) {
		std::map<std::string, std::string>::iterator it = settings.begin();
		while (it != settings.end()) {
			std::string key = it->first;
			std::string value = it->second;
			if (key == "windowMode" || key == "WINDOW_MODE") {
				if (value == "headless" || value == "HEADLESS") {
					windowMode = HEADLESS;
				}
				if (value == "windowed" || value == "WINDOWED") {
					windowMode = WINDOWED;
				}
				if (value == "fullscreen" || value == "FULLSCREEN") {
					windowMode = FULLSCREEN;
				}
			}
			if (key == "width" || key == "WIDTH") {
				width = std::stoi(value);
			}
			if (key == "height" || key == "HEIGHT") {
				height = std::stoi(value);
			}
			if (key == "api" || key == "API") {
				if (value == "vulkan" || value == "VULKAN" || value == "vk" || value == "VK") {
					api = VULKAN;
				}
				else if (value == "opengl" || value == "OPENGL" || value == "gl" || value == "GL") {
					api = OPEN_GL;
				}
				else if (value == "directx" || value == "DIRECTX" || value == "dx" || value == "DX") {
					api = DIRECT_X;
				}
			}
			it++;
		}
	}
};