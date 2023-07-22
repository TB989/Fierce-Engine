#pragma once

#include "InputSystem.h"
#include "src/core/Core.h"

class Action_StopEngine: public Action {
public:
	Action_StopEngine(Core* core);
	void doAction(float dd) override;

private:
	Core* m_core;
};