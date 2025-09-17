#include "GUIPanel.h"

namespace Fierce {

	void GUIPanel::onMouseMoved(int x, int y){
		if (m_x<x&&x<m_x+m_width&&m_y<y&&y<m_y+m_height) {
			m_isMouseOver = true;
		}
		else {
			m_isMouseOver = false;
		}
	}

	void Fierce::GUIPanel::draw(GraphicsContext* g){
		g->setColor(m_backgroundColor->getR(),m_backgroundColor->getG(),m_backgroundColor->getB());
		g->drawRect(m_x,m_y,m_width,m_height);
	}

	void GUIPanel::calculatePreferredSize(){

	}
}