#pragma once

#include "src/gameplay/Player.h"

#include "src/Bindable.h"

namespace Fierce {

	class Transform3D;

	class Range_MoveForward :public Range {
	public:
		Range_MoveForward(Transform3D* viewTransform,Player* player);

		void onRangeChanged(float delta) override;

	private:
		Transform3D* m_viewTransform = nullptr;
		Player* m_player = nullptr;
	};
}