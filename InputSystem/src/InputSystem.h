#pragma once

#include "InputBindings.h"

#include "src/Bindable.h"
#include "src/System.h"

namespace Fierce {

	class LoggingSystem;
	class Logger;
	class InputContext;

	class InputSystem :public System{
	public:
		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

		void switchMouseMode(bool rawMouse);
		InputContext* getActiveContext() { return m_activeContext; }

	public:
		InputSystem(LoggingSystem* loggingSystem);

		void addAction(BINDING binding, Action* action,bool rawInput);
		void removeAction(BINDING binding, bool rawInput);

		void addState(BINDING binding, State* state, bool rawInput);
		void removeState(BINDING binding, bool rawInput);

		void addRange(BINDING binding, Range* range, bool rawInput);
		void removeRange(BINDING binding, bool rawInput);

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger=nullptr;

		InputContext* m_inputContext_raw=nullptr;
		InputContext* m_inputContext_normal=nullptr;

		InputContext* m_activeContext=nullptr;
	};
}//end namespace