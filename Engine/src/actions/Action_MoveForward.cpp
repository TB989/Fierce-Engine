#include "Action_MoveForward.h"

#define _USE_MATH_DEFINES
#include <math.h>

Action_MoveForward::Action_MoveForward(Transform3D* camera,float speed){
	m_camera = camera;
	m_speed = speed;
}

void Action_MoveForward::doAction(float dd){
	Vector3f* angles = m_camera->getRotation();
	Vector3f* position = m_camera->getPosition();

	float angleY = angles->getY();
	float s = sin(M_PI / 180.0f * angleY);
	float c = cos(M_PI / 180.0f * angleY);
	position->setX(position->getX() + s * m_speed);
	position->setZ(position->getZ() - c * m_speed);
}