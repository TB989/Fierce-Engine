#include "Transform.h"

Transform2D::Transform2D() {
	x = 0;
	y = 0;
	scaleX = 1;
	scaleY = 1;
	m_rotation = 0;
}

Transform2D::Transform2D(Transform2D& transform) {
	x = transform.getPosition()->getX();
	y = transform.getPosition()->getY();
	scaleX = transform.getScale()->getX();
	scaleY = transform.getScale()->getY();
	m_rotation = transform.getRotation();
}

Transform2D::Transform2D(float x, float y, float scaleX, float scaleY, float rotation) {
	this->x = x;
	this->y = y;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->m_rotation = rotation;
}

Transform2D::Transform2D(Vector2f* position, Vector2f* scale, float rotation) {
	x = position->getX();
	y = position->getY();
	scaleX = scale->getX();
	scaleY = scale->getY();
	m_rotation = rotation;
}

Transform2D::~Transform2D() {
	
}

Transform3D::Transform3D() {
	x = 0;
	y = 0;
	z = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;
}

Transform3D::Transform3D(Transform3D& transform) {
	x = transform.getPosition()->getX();
	y = transform.getPosition()->getY();
	z = transform.getPosition()->getZ();
	scaleX = transform.getScale()->getX();
	scaleY = transform.getScale()->getY();
	scaleZ = transform.getScale()->getZ();
	rotationX = transform.getRotation()->getX();
	rotationY = transform.getRotation()->getY();
	rotationZ = transform.getRotation()->getZ();
}

Transform3D::Transform3D(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	this->rotationX = rotationX;
	this->rotationY = rotationY;
	this->rotationZ = rotationZ;
}

Transform3D::Transform3D(Vector3f* position, Vector3f* scale, Vector3f* rotation) {
	x = position->getX();
	y = position->getY();
	z = position->getZ();
	scaleX = scale->getX();
	scaleY = scale->getY();
	scaleZ = scale->getZ();
	rotationX = rotation->getX();
	rotationY = rotation->getY();
	rotationZ = rotation->getZ();
}

Transform3D::~Transform3D() {
	
}