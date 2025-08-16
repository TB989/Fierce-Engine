#include "GUIButton.h"

#include "GUIHelper.h"

namespace Fierce {

	Fierce::GUIButton::GUIButton(std::string text) {
		m_text = text;
	}

	void GUIButton::draw(GraphicsContext* g) {
		m_width = m_preferredWidth = GUIHelper::getStringWidth(m_text, m_font, m_fontSize, g);
		m_height = m_preferredHeight = GUIHelper::getStringHeight(m_text, m_font, m_fontSize, g);

		g->setColor(m_backgroundColor->getR(), m_backgroundColor->getG(), m_backgroundColor->getB());
		g->drawRect(m_x, m_y, m_width + 2 * GAP, m_height + 2 * GAP);

		g->setColor(m_foregroundColor->getR(), m_foregroundColor->getG(), m_foregroundColor->getB());
		g->setFont(m_font, m_fontSize);
		g->drawText(m_x + GAP, m_y + GAP, m_text);
	}
}