#include "Range_controlCamera.h"

#include "src/math/ITransform.h"
#include <iostream>

namespace Fierce {
	Range_controlCamera::Range_controlCamera(ITransform3D* viewTransform){
		m_viewTransform = viewTransform;
	}

	void Range_controlCamera::onRangeChanged(float x, float y){
		float angleX = m_viewTransform->getRotation()->getX();
		float angleY = m_viewTransform->getRotation()->getY();

		std::cout << "X:" << x << "\n";
		std::cout << "Y:" << y << "\n";

		//Look up/down
		angleX -= y;

		if (angleX > 45.0f) {
			angleX = 45.0f;
		}
		if (angleX < -45.0f) {
			angleX = -45.0f;
		}

		//Look right/left
		angleY -= x;

		if (angleY > 360.0f) {
			angleY -= 360.0f;
		}
		if (angleY < 0.0f) {
			angleY += 360.0f;
		}

		m_viewTransform->getRotation()->setX(angleX);
		m_viewTransform->getRotation()->setY(angleY);
	}
}