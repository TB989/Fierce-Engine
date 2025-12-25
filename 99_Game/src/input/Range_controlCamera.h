#pragma once

#include "src/systems/IInputSystem.h"

namespace Fierce {

	class ITransform3D;

	class Range_controlCamera :public Range {
	public:
		Range_controlCamera(ITransform3D* viewTransform);

		void onRangeChanged(float x, float y) override;

	private:
		ITransform3D* m_viewTransform=nullptr;
	};
}