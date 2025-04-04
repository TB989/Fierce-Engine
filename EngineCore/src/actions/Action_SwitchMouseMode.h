#pragma once

#include "src/utils/Bindable.h"

#include "src/Win32/Win32_Window.h"

namespace Fierce {

	class InputSystem;

	class Action_SwitchMouseMode :public Action {
	public:
		Action_SwitchMouseMode(InputSystem* inputSystem,Window* window,bool switchToRawInput);

		void onAction() override;

	private:
		InputSystem* m_inputSystem=nullptr;
		Win32_Window* m_window=nullptr;
		bool m_switchToRawInput=false;
	};
}