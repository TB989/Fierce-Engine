#include "Win32_TimeDateSystem.h"

#include "Win32_Timer.h"

namespace Fierce {

	Win32_TimeDateSystem::Win32_TimeDateSystem(){
		getDateTime();
	}

	Win32_TimeDateSystem::~Win32_TimeDateSystem(){

	}

	void Win32_TimeDateSystem::initSystem(std::string m_assetDirectory){
		if (m_loggingSystem != nullptr) {
			m_logger = m_loggingSystem->createLogger("TIME", true, "ALL_LOGS");
			m_logger->info("Init time date system");
		}
	}

	void Win32_TimeDateSystem::linkSystem(System* system){
		if (dynamic_cast<LoggingSystem*>(system)) {
			m_loggingSystem = (LoggingSystem*)system;
		}
	}

	void Win32_TimeDateSystem::updateSystem(){
		getDateTime();
	}

	void Win32_TimeDateSystem::cleanUpSystem(){
		for (Timer* timer:m_timers) {
			delete timer;
		}

		if (m_logger != nullptr) {
			m_logger->info("Clean up time date system");
			m_loggingSystem->deleteLogger(m_logger);
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

	void Win32_TimeDateSystem::getDateTime(){
		m_time = time(nullptr);
		localtime_s(&m_localTime, &m_time);
		m_year = m_localTime.tm_year + 1900;
		m_month = m_localTime.tm_mon + 1;
		m_day = m_localTime.tm_mday;
		m_hours = m_localTime.tm_hour;
		m_minutes = m_localTime.tm_min;
		m_seconds = m_localTime.tm_sec;
	}
}