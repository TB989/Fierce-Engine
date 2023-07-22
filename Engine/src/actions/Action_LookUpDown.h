#pragma once

#include "InputSystem.h"
#include "MathLibrary.h"

#include "src/utils/Logging.h"

class Action_LookUpDown : public Action {
public:
	Action_LookUpDown(Transform3D* camera, float speed);
	void doAction(float dd) override;
private:
	Transform3D* m_camera;
	float m_speed;
};
