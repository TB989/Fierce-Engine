#pragma once

#include "src/Bindable.h"

namespace Fierce {

	class Transform3D;

	class Range_lookUpDown :public Range {
	public:
		Range_lookUpDown(Transform3D* viewTransform);

		void onRangeChanged(float delta) override;

	private:
		Transform3D* m_viewTransform=nullptr;
	};
}