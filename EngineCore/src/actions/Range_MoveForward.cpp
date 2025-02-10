#include "Range_MoveForward.h"

#include "src/Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Fierce {
	Range_MoveForward::Range_MoveForward(Transform3D* viewTransform, Player* player) {
		m_viewTransform = viewTransform;
		m_player = player;
	}

	void Range_MoveForward::onRangeChanged(float delta) {
		if (!m_player->m_moveForward) {
			return;
		}

		float angle = m_viewTransform->getRotation()->getY();
		Vector3f* position = m_viewTransform->getPosition();

		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);
		position->setX(position->getX() - s * 0.1f);
		position->setZ(position->getZ() + c * 0.1f);
	}
}