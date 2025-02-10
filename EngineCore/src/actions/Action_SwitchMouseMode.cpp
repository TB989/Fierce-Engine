#include "Action_SwitchMouseMode.h"

#include "src/InputSystem.h"
#include "src/Window.h"

namespace Fierce {

	Action_SwitchMouseMode::Action_SwitchMouseMode(InputSystem* inputSystem, Window* window, bool switchToRawInput){
		m_inputSystem = inputSystem;
		m_window = window;
		m_switchToRawInput = switchToRawInput;
	}

	void Action_SwitchMouseMode::onAction(){
		if (m_switchToRawInput) {
			m_inputSystem->switchMouseMode(m_switchToRawInput);
			m_window->activateRawInput();
		}
		else {
			m_inputSystem->switchMouseMode(m_switchToRawInput);
			m_window->deactivateRawInput();
		}
	}
}