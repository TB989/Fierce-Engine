#pragma once

#include <vector>
#include <unordered_map>

#include "Windows.h"

#include "src/include/LoggingSystem.h"

namespace Fierce {

	class TimeDateSystem;

	class Win32_LoggingSystem:public LoggingSystem {
	public:
		Win32_LoggingSystem(TimeDateSystem* timeDateSystem);

		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Logger* createLogger(std::string name) override;
		Logger* createLogger(std::string name,bool logToConsole, std::string file) override;
		void deleteLogger(Logger* logger) override;

	private:
		TimeDateSystem* m_timeDateSystem = nullptr;

		HANDLE m_handle=NULL;
		std::unordered_map<std::string, FILE*> m_openFiles;
		std::vector<Logger*> m_loggers;
	};

}//end namespace