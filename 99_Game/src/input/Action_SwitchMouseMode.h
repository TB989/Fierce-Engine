#pragma once

#include "src/systems/IInputSystem.h"

namespace Fierce {

	class IInputSystem;
	class IWindow;

	class Action_SwitchMouseMode :public Action {
	public:
		Action_SwitchMouseMode(IInputSystem* inputSystem,IWindow* window,bool switchToRawInput);

		void onAction() override;

	private:
		IInputSystem* m_inputSystem=nullptr;
		IWindow* m_window=nullptr;
		bool m_switchToRawInput=false;
	};
}