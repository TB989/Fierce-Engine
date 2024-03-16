#include "Action_LookUpDown.h"

Action_LookUpDown::Action_LookUpDown(World* world, EntityId camera, float speed) {
	m_camera = world->ecs->getComponent<Transform3D>(camera);
	m_speed = speed;
}

void Action_LookUpDown::doAction(float dd) {
	Vector3f* angles = m_camera->getRotation();

	float angleX = angles->getX() - m_speed * dd;
	if (angleX > 45.0f) {
		angleX = 45.0f;
	}
	if (angleX < -45.0f) {
		angleX = -45.0f;
	}
	angles->setX(angleX);
}