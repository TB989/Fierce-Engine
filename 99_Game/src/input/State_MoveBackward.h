#pragma once

#include "src/layers/Player.h"

#include "src/systems/IInputSystem.h"

namespace Fierce {

	class State_MoveBackward :public State {
	public:
		State_MoveBackward(Player* player);

		void onStateChanged(bool isActivated) override;

	private:
		Player* m_player = nullptr;
	};
}