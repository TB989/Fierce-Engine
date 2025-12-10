#pragma once

#include "src/PlatformLayer/utils/Bindable.h"

namespace Fierce {

	class Transform3D;

	class Range_controlCamera :public Range {
	public:
		Range_controlCamera(Transform3D* viewTransform);

		void onRangeChanged(float x, float y) override;

	private:
		Transform3D* m_viewTransform=nullptr;
	};
}