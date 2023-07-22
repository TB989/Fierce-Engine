#include "Action_LookRightLeft.h"

Action_LookRightLeft::Action_LookRightLeft(Transform3D* camera, float speed){
	m_camera = camera;
	m_speed = speed;
}

void Action_LookRightLeft::doAction(float dd) {
	Vector3f* angles = m_camera->getRotation();

	float angleY = angles->getY() - m_speed * dd;
	angles->setY(angleY);
}