#pragma once

#include "GUIPanel.h"

#include "src/GUI/GraphicsContext.h"

#include <string>

namespace Fierce {
	class GUILabel : public GUIPanel{
	public:
		GUILabel(std::string text);

		void draw(GraphicsContext* g);
		void calculatePreferredSize();

	private:
		float GAP = 2.0f;

		std::string m_text;
	};
}