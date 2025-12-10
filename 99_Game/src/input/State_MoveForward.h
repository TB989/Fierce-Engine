#pragma once

#include "src/layers/Player.h"

#include "src/Bindable.h"

namespace Fierce {

	class State_MoveForward :public State {
	public:
		State_MoveForward(Player* player);

		void onStateChanged(bool isActivated) override;

	private:
		Player* m_player=nullptr;
	};
}
