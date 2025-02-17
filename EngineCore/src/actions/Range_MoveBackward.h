#pragma once

#include "src/gameplay/Player.h"

#include "src/Bindable.h"

namespace Fierce {

	class Transform3D;

	class Range_MoveBackward :public Range {
	public:
		Range_MoveBackward(Transform3D* viewTransform,Player* player,float speed);

		void onRangeChanged(float delta) override;

	private:
		Transform3D* m_viewTransform = nullptr;
		Player* m_player = nullptr;
		float m_speed;
	};
}
