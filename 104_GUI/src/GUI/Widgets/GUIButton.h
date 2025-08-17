#pragma once

#include "GUIPanel.h"

#include <string>

namespace Fierce {
	class GUIButton : public GUIPanel {
	public:
		GUIButton(std::string text);

		void draw(GraphicsContext* g);
	private:
		float GAP = 2.0f;

		std::string m_text;
	};
}