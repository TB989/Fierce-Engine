#include "Action_SwitchMouseMode.h"

#include "src/PlatformLayer/include/InputSystem.h"
#include "src/PlatformLayer/include/WindowSystem.h"

namespace Fierce {

	Action_SwitchMouseMode::Action_SwitchMouseMode(InputSystem* inputSystem, Window* window, bool switchToRawInput){
		m_inputSystem = inputSystem;
		m_window = window;
		m_switchToRawInput = switchToRawInput;
	}

	void Action_SwitchMouseMode::onAction(){
		if (m_switchToRawInput) {
			m_inputSystem->switchMouseMode(m_window,m_switchToRawInput);
		}
		else {
			m_inputSystem->switchMouseMode(m_window,m_switchToRawInput);
		}
	}
}