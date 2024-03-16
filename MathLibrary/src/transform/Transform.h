#pragma once

#include "src/vector/Vector.h"

class Transform {

};

class Transform2D : Transform {
private:
	float x;
	float y;
	float scaleX;
	float scaleY;
	float m_rotation;
public:
	Transform2D();
	Transform2D(Transform2D& transform);
	Transform2D(float x, float y, float scaleX, float scaleY, float rotation);
	Transform2D(Vector2f* position, Vector2f* scale, float rotation);
	~Transform2D();

	Vector2f* getPosition() { return new Vector2f(x,y); }
	Vector2f* getScale() { return new Vector2f(scaleX, scaleY);}
	float getRotation() { return m_rotation; }
};

class Transform3D : Transform {
private:
	float x;
	float y;
	float z;
	float scaleX;
	float scaleY;
	float scaleZ;
	float rotationX;
	float rotationY;
	float rotationZ;
public:
	Transform3D();
	Transform3D(Transform3D& transform);
	Transform3D(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ);
	Transform3D(Vector3f* position, Vector3f* scale, Vector3f* rotation);
	~Transform3D();

	Vector3f* getPosition() { return new Vector3f(x,y,z); }
	Vector3f* getScale() { return new Vector3f(scaleX, scaleY, scaleZ); }
	Vector3f* getRotation() { return new Vector3f(rotationX, rotationY, rotationZ);}
};