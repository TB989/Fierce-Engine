#include "Range_PrintMousePosition.h"

namespace Fierce {

	Range_PrintMousePosition::Range_PrintMousePosition(GUILabel* label_x, std::string text_x, GUILabel* label_y, std::string text_y) {
		m_labelX = label_x;
		m_textX = text_x;
		m_labelY = label_y;
		m_textY = text_y;
	}

	void Range_PrintMousePosition::onRangeChanged(float x, float y) {
		std::string tempTextX = m_textX;
		std::string tempTextY = m_textY;
		tempTextX.append(std::to_string((int)x));
		tempTextY.append(std::to_string((int)y));
		m_labelX->setText(tempTextX);
		m_labelY->setText(tempTextY);
	}
}