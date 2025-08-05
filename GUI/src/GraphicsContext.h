#pragma once

#include "src/utils/FierceStrings.h"

namespace Fierce {
	class GraphicsContext {
	public:
		virtual void setColor(int r, int g, int b)=0;
		virtual void setFont(std::string name, int size) = 0;

		virtual void drawRect(int x, int y, int width, int height)=0;
		virtual void drawText(int x, int y, std::string text)=0;
	};
}