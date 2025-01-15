#include "State_Test.h"

#include "src/Logger.h"

namespace Fierce {
	State_Test::State_Test(Logger* logger){
		m_logger = logger;
	}

	void State_Test::onStateChanged(bool isActivated){
		if (isActivated) {
			m_logger->info("State activated.");
		}
		else {
			m_logger->info("State deactivated.");
		}
	}
}