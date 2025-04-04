#include "Win32_TimeDateSystem.h"

#include "Win32_Timer.h"

namespace Fierce {

	void Win32_TimeDateSystem::initSystem(){
		updateSystem();
	}

	void Win32_TimeDateSystem::updateSystem(){
		m_time=time(nullptr);
		localtime_s(&m_localTime ,&m_time);
		m_year=m_localTime.tm_year + 1900;
		m_month=m_localTime.tm_mon + 1;
		m_day=m_localTime.tm_mday;
		m_hours = m_localTime.tm_hour;
		m_minutes = m_localTime.tm_min;
		m_seconds = m_localTime.tm_sec;
	}

	void Win32_TimeDateSystem::cleanUpSystem(){
		for (Timer* timer:m_timers) {
			delete timer;
		}
	}

	Timer* Win32_TimeDateSystem::createTimer(){
		Timer* timer = new Win32_Timer();
		m_timers.push_back(timer);
		return timer;
	}

	void Win32_TimeDateSystem::deleteTimer(Timer* timer){
		auto it = std::find(m_timers.begin(), m_timers.end(), timer);
		if (it != m_timers.end()) {
			m_timers.erase(it);
			delete timer;
		}
	}
}