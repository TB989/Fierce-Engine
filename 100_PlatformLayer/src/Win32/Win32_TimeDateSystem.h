#pragma once

#include "src/include/TimeDateSystem.h"

#include "time.h"

#include <vector>

namespace Fierce {

	class Win32_TimeDateSystem :public TimeDateSystem {
	public:
		void initSystem(std::string assetDirectory) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Timer* createTimer() override;
		void deleteTimer(Timer* timer) override;

	private:
		time_t m_time=NULL;
		tm m_localTime;

		std::vector<Timer*> m_timers;
	};

}//end namespace