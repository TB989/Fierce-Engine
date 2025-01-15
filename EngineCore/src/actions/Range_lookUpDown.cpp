#include "Range_lookUpDown.h"

#include "src/Transform.h"

namespace Fierce {
	Range_lookUpDown::Range_lookUpDown(Transform3D* viewTransform){
		m_viewTransform = viewTransform;
	}

	void Range_lookUpDown::onRangeChanged(float delta){
		float angle = m_viewTransform->getRotation()->getX();

		angle -= delta;

		if (angle > 45.0f) {
			angle = 45.0f;
		}
		if (angle < -45.0f) {
			angle = -45.0f;
		}

		m_viewTransform->getRotation()->setX(angle);
	}
}