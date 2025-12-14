#pragma once

#include "src/systems/ITimeDateSystem.h"
#include "src/PlatformLayer/include/LoggingSystem.h"

#include "time.h"

#include <vector>

namespace Fierce {

	class Win32_TimeDateSystem :public ITimeDateSystem, public System {
	public:
		Win32_TimeDateSystem();
		~Win32_TimeDateSystem();

	public:
		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

	public:
		int getYear() override;
		int getMonth() override;
		int getDay() override;

		int getHours() override;
		int getMinutes() override;
		int getSeconds() override;

		ITimer* createTimer() override;
		void deleteTimer(ITimer* timer) override;

	private:
		void getDateTime();

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		time_t m_time=NULL;
		tm m_localTime;

		int m_year = -1;
		int m_month = -1;
		int m_day = -1;

		int m_hours = -1;
		int m_minutes = -1;
		int m_seconds = -1;

		std::vector<ITimer*> m_timers;
	};

}//end namespace