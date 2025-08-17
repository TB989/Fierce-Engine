#include "GUILabel.h"

#include "src/GUI/GUIHelper.h"

namespace Fierce {

	Fierce::GUILabel::GUILabel(std::string text){
		m_text = text;

		calculatePreferredSize();
	}

	void GUILabel::draw(GraphicsContext* g){
		g->setColor(m_backgroundColor->getR(), m_backgroundColor->getG(), m_backgroundColor->getB());
		g->drawRect(m_x,m_y,m_width+2*GAP,m_height+2*GAP);

		g->setColor(m_foregroundColor->getR(), m_foregroundColor->getG(), m_foregroundColor->getB());
		g->setFont(m_font,m_fontSize);
		g->drawText(m_x+GAP,m_y+GAP, m_text);
	}

	void GUILabel::calculatePreferredSize() {
		m_width = m_preferredWidth = GUIHelper::getStringWidth(m_text, m_font, m_fontSize);
		m_height = m_preferredHeight = GUIHelper::getStringHeight(m_text, m_font, m_fontSize);
	}

}