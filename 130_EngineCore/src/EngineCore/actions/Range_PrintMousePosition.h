#pragma once

#include "src/PlatformLayer/utils/Bindable.h"
#include "src/GUI/Widgets/GUILabel.h"

#include "Point.h"

namespace Fierce {

	class Range_PrintMousePosition :public Range {
	public:
		Range_PrintMousePosition(Point* point, bool setX, GUILabel* label,std::string text);

		void onRangeChanged(float delta) override;

	private:
		GUILabel* m_label = nullptr;
		std::string m_text;
		Point* m_point = nullptr;
		bool m_set_x = false;
	};
}
