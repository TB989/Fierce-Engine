#pragma once

#include "InputSystem.h"
#include "MathLibrary.h"

class Action_MoveForward : public Action {
public:
	Action_MoveForward(Transform3D* camera,float  speed);
	void doAction(float dd) override;
private:
	Transform3D* m_camera;
	float m_speed;
};