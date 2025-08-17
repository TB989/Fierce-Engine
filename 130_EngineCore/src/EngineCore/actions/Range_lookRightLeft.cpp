#include "Range_lookRightLeft.h"

#include "src/MathLibrary/Transform.h"

namespace Fierce {

	Range_lookRightLeft::Range_lookRightLeft(Transform3D* viewTransform){
		m_viewTransform = viewTransform;
	}

	void Range_lookRightLeft::onRangeChanged(float delta){
		float angle = m_viewTransform->getRotation()->getY();

		angle -= delta;

		if (angle > 360.0f) {
			angle -=360.0f;
		}
		if (angle < 0.0f) {
			angle +=360.0f;
		}

		m_viewTransform->getRotation()->setY(angle);
	}
}