#pragma once

#include "src/systems/IInputSystem.h"
#include "src/systems/ILoggingSystem.h"
#include "src/systems/IWindowSystem.h"

namespace Fierce {
	class InputSystem:public IInputSystem{
	public:
		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		std::string getName() override;

		void addAction(BINDING binding, Action* action, bool rawInput) override;
		void removeAction(BINDING binding, bool rawInput) override;

		void addState(BINDING binding, State* state, bool rawInput) override;
		void removeState(BINDING binding, bool rawInput) override;

		void addRange(BINDING binding, Range* range, bool rawInput) override;
		void removeRange(BINDING binding, bool rawInput) override;

		void switchMouseMode(IWindow* window, bool rawMouse) override;
		InputContext* getActiveContext() override;

	private:
		ILoggingSystem* m_loggingSystem = nullptr;
		ILogger* m_logger = nullptr;

		InputContext* m_inputContext_raw = nullptr;
		InputContext* m_inputContext_normal = nullptr;

		InputContext* m_activeContext = nullptr;
	};
}//end namespace