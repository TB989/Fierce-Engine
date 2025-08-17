#pragma once

#include "src/EngineCore/gameplay/Player.h"

#include "src/PlatformLayer/utils/Bindable.h"

namespace Fierce {

	class Transform3D;

	class Range_MoveForward :public Range {
	public:
		Range_MoveForward(Transform3D* viewTransform,Player* player,float speed);

		void onRangeChanged(float delta) override;

	private:
		Transform3D* m_viewTransform = nullptr;
		Player* m_player = nullptr;
		float m_speed;
	};
}