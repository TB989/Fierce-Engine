#include "Action_StopEngine.h"

Action_StopEngine::Action_StopEngine(Core* core){
	m_core = core;
}

void Action_StopEngine::doAction(float dd){
	m_core->stop();
}