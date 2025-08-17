#include "Action_StopEngine.h"

#include "src/EngineCore/core/EngineCore.h"

namespace Fierce {

	Action_StopEngine::Action_StopEngine(EngineCore* core){
		m_core = core;
	}

	void Fierce::Action_StopEngine::onAction(){
		m_core->stop();
	}

}//end namespace