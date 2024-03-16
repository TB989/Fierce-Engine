#pragma once

#include "InputSystem.h"
#include "MathLibrary.h"
#include "src/world/World.h"

class Action_MoveForward : public Action {
public:
	Action_MoveForward(World* world, EntityId camera, float speed);
	void doAction(float dd) override;
private:
	Transform3D* m_camera;
	float m_speed;
};