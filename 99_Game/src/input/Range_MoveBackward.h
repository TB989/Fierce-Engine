#pragma once

#include "src/layers/Player.h"

#include "src/Bindable.h"

namespace Fierce {

	class ITransform3D;

	class Range_MoveBackward :public Range {
	public:
		Range_MoveBackward(ITransform3D* viewTransform,Player* player,float speed);

		void onRangeChanged(float x, float y) override;

	private:
		ITransform3D* m_viewTransform = nullptr;
		Player* m_player = nullptr;
		float m_speed;
	};
}
