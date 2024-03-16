#include "Action_MoveBackward.h"

#include "src/utils/Logging.h"

#define _USE_MATH_DEFINES
#include <math.h>

Action_MoveBackward::Action_MoveBackward(World* world, EntityId camera, float speed) {
	m_camera = world->ecs->getComponent<Transform3D>(camera);
	m_speed = speed;
}

void Action_MoveBackward::doAction(float dd) {
	Vector3f* angles = m_camera->getRotation();
	Vector3f* position = m_camera->getPosition();

	float angleY = angles->getY();
	float s = sin(M_PI / 180.0f * angleY);
	float c = cos(M_PI / 180.0f * angleY);
	position->setX(position->getX() - s * m_speed);
	position->setZ(position->getZ() + c * m_speed);
}