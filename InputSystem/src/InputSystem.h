#pragma once

#include "src/Action.h"
#include "src/System.h"

#include "unordered_map"

namespace Fierce {

	class LoggingSystem;
	class Logger;

	class InputSystem :public System{
	public:
		enum BINDING {
			KEY_ESC
		};

	public:
		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

	public:
		InputSystem(LoggingSystem* loggingSystem);

		void addAction(BINDING binding,Action* action);
		void removeAction(BINDING binding);

	public:
		void onKeyDown(BINDING binding);

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger=nullptr;

		std::unordered_map<BINDING,Action*> m_actions;
	};
}//end namespace