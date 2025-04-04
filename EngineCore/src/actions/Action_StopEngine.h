#pragma once

#include "src/utils/Bindable.h"

namespace Fierce {

	class EngineCore;

	class Action_StopEngine :public Action {
	public:
		Action_StopEngine(EngineCore* core);

		void onAction() override;

	private:
		EngineCore* m_core;
	};

}//end namespace