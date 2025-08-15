#pragma once

#include "src/include/TimeDateSystem.h"
#include "src/include/LoggingSystem.h"

#include "time.h"

#include <vector>

namespace Fierce {

	class Win32_TimeDateSystem :public TimeDateSystem {
	public:
		Win32_TimeDateSystem();
		~Win32_TimeDateSystem();

		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Timer* createTimer() override;
		void deleteTimer(Timer* timer) override;

	private:
		void getDateTime();

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		time_t m_time=NULL;
		tm m_localTime;

		std::vector<Timer*> m_timers;
	};

}//end namespace