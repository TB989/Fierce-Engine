#include "State_MoveForward.h"

#include "src/Logger.h"

namespace Fierce {
	State_MoveForward::State_MoveForward(Player* player) {
		m_player = player;
	}

	void State_MoveForward::onStateChanged(bool isActivated) {
		m_player->m_moveForward = isActivated;
	}
}