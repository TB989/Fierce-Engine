#pragma once

#include "System.h"

#include <string>

namespace Fierce {

	enum WINDOW_MODE {
		WINDOWED, FULLSCREEN
	};

	class IWindow {
	public:
		virtual void pollEvents()=0;
		virtual void show()=0;
		virtual void onResize(int width, int height)=0;

		virtual std::string getTitle()=0;
		virtual bool isFullcreen()=0;
		virtual int getWidth()=0;
		virtual int getHeight()=0;

		virtual void activateRawInput()=0;
		virtual void deactivateRawInput()=0;
	};

	class IWindowSystem:public System{
	public:
		virtual IWindow* createWindow(std::string title, WINDOW_MODE windowMode, int width, int height)=0;
		virtual void deleteWindow(IWindow* window)=0;
	};

};