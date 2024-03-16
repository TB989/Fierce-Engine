#include "Action_LookRightLeft.h"

Action_LookRightLeft::Action_LookRightLeft(World* world, EntityId camera, float speed){
	m_camera = world->ecs->getComponent<Transform3D>(camera);
	m_speed = speed;
}

void Action_LookRightLeft::doAction(float dd) {
	Vector3f* angles = m_camera->getRotation();

	float angleY = angles->getY() - m_speed * dd;
	angles->setY(angleY);
}