#pragma once

#include "src/PlatformLayer/utils/Bindable.h"

namespace Fierce {

	class InputSystem;
	class Window;

	class Action_SwitchMouseMode :public Action {
	public:
		Action_SwitchMouseMode(InputSystem* inputSystem,Window* window,bool switchToRawInput);

		void onAction() override;

	private:
		InputSystem* m_inputSystem=nullptr;
		Window* m_window=nullptr;
		bool m_switchToRawInput=false;
	};
}