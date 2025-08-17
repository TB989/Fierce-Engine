#pragma once

#include "src/EngineCore/gameplay/Player.h"

#include "src/PlatformLayer/utils/Bindable.h"

namespace Fierce {

	class State_MoveBackward :public State {
	public:
		State_MoveBackward(Player* player);

		void onStateChanged(bool isActivated) override;

	private:
		Player* m_player = nullptr;
	};
}