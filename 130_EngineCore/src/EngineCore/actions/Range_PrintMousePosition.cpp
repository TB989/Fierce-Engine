#include "Range_PrintMousePosition.h"

namespace Fierce {

	Range_PrintMousePosition::Range_PrintMousePosition(Point* point, bool setX, GUILabel* label,std::string text) {
		m_label = label;
		m_text = text;
		m_point = point;
		m_set_x = setX;
	}

	void Range_PrintMousePosition::onRangeChanged(float delta) {
		std::string tempText = m_text;
		tempText.append(std::to_string((int)delta));
		m_label->setText(tempText);

		if (m_set_x) {
			m_point->m_x = delta;
		}
		else {
			m_point->m_y = delta;
		}
	}
}