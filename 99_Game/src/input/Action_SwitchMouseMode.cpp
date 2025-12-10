#include "Action_SwitchMouseMode.h"

#include "src/systems/IInputSystem.h"
#include "src/systems/IWindowSystem.h"

namespace Fierce {

	Action_SwitchMouseMode::Action_SwitchMouseMode(IInputSystem* inputSystem, IWindow* window, bool switchToRawInput){
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