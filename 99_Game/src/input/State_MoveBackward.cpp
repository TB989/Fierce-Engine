#include "State_MoveBackward.h"

namespace Fierce {
	State_MoveBackward::State_MoveBackward(Player* player) {
		m_player = player;
	}

	void State_MoveBackward::onStateChanged(bool isActivated) {
		m_player->m_moveBackward = isActivated;
	}
}