#pragma once

#include <string>

#include "src/systems/System.h"

namespace Fierce {

	class Window {
	public:
		enum WINDOW_MODE {
			WINDOWED, FULLSCREEN
		};

	public:
		Window(std::string title, WINDOW_MODE windowMode, int width, int height) {
			m_title = title;
			m_isFullscreen = windowMode == FULLSCREEN ? true : false;
			m_width = width;
			m_height = height;
		}

		virtual ~Window() {};

		virtual void pollEvents()=0;
		virtual void show()=0;
		virtual void onResize(int width, int height) = 0;

		std::string getTitle(){ return m_title; }
		bool isFullcreen() { return m_isFullscreen; }
		int getWidth() { return m_width; }
		int getHeight() { return m_height; }

		virtual void activateRawInput()=0;
		virtual void deactivateRawInput()=0;

	protected:
		std::string m_title = "";
		bool m_isFullscreen = false;
		int m_width=-1;
		int m_height=-1;
	};

	class WindowSystem :public System {
	public:
		virtual ~WindowSystem() = default;

		virtual Window* createWindow(std::string title, Window::WINDOW_MODE windowMode, int width, int height)=0;
		virtual void deleteWindow(Window* window)=0;
	};

};