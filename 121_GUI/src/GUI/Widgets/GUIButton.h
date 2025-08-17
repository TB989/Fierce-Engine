#pragma once

#include "GUIPanel.h"

#include <string>

#include "src/GUI/GraphicsContext.h"

namespace Fierce {
	class GUIButton : public GUIPanel {
	public:
		GUIButton(std::string text);

		void draw(GraphicsContext* g);
		void calculatePreferredSize();

	private:
		float GAP = 2.0f;

		std::string m_text;
	};
}