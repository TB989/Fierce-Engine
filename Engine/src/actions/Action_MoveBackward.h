#pragma once

#include "InputSystem.h"
#include "MathLibrary.h"
#include "src/world/World.h"

class Action_MoveBackward : public Action {
public:
	Action_MoveBackward(World* world, EntityId camera, float speed);
	void doAction(float dd) override;
private:
	Transform3D* m_camera;
	float m_speed;
};