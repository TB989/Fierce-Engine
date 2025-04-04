#pragma once

#include "src/utils/Bindable.h"

namespace Fierce {

	class Transform3D;

	class Range_lookRightLeft :public Range {
	public:
		Range_lookRightLeft(Transform3D* viewTransform);

		void onRangeChanged(float delta) override;

	private:
		Transform3D* m_viewTransform = nullptr;
	};
}