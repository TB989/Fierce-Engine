#pragma once

#include "src/Action.h"

namespace Fierce {

	class EngineCore;

	class Action_StopEngine :public Action {
	public:
		Action_StopEngine(EngineCore* core);

		void run() override;

	private:
		EngineCore* m_core;
	};

}//end namespace