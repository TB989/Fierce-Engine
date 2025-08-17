#pragma once

#include "src/EngineCore/gameplay/Player.h"

#include "src/PlatformLayer/utils/Bindable.h"

namespace Fierce {

	class State_MoveForward :public State {
	public:
		State_MoveForward(Player* player);

		void onStateChanged(bool isActivated) override;

	private:
		Player* m_player=nullptr;
	};
}
