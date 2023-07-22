#pragma once

#include "InputSystem.h"
#include "MathLibrary.h"

class Action_LookRightLeft : public Action {
public:
	Action_LookRightLeft(Transform3D* camera, float speed);
	void doAction(float dd) override;
private:
	Transform3D* m_camera;
	float m_speed;
};