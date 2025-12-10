#pragma once

#include "src/PlatformLayer/utils/Bindable.h"
#include "src/GUI/Widgets/GUILabel.h"

namespace Fierce {

	class Range_PrintMousePosition :public Range {
	public:
		Range_PrintMousePosition(GUILabel* label_x,std::string text_x, GUILabel* label_y, std::string text_y);

		void onRangeChanged(float x, float y) override;

	private:
		GUILabel* m_labelX = nullptr;
		std::string m_textX;
		GUILabel* m_labelY = nullptr;
		std::string m_textY;
	};
}
