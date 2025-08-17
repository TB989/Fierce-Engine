#include "GUIPanel.h"


namespace Fierce {

	void Fierce::GUIPanel::draw(GraphicsContext* g){
		g->setColor(m_backgroundColor->getR(),m_backgroundColor->getG(),m_backgroundColor->getB());
		g->drawRect(m_x,m_y,m_width,m_height);
	}

	void GUIPanel::calculatePreferredSize(){

	}
}