#pragma once

#include "Logger.h"

#include "src/FierceStrings.h"
#include "src/System.h"
#include <unordered_map>
#include <vector>
#include <Windows.h>
#include "time.h"
#include <filesystem>

namespace Fierce {

	class LoggingSystem:public System {
	public:
		LoggingSystem(std::string logDirectory);
		~LoggingSystem();

		void initSystem() override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Logger* createLogger(std::string name);
		Logger* createLogger(std::string name,bool logToConsole, std::string file);
		void deleteLogger(Logger* logger);

	private:
		HANDLE m_handle=NULL;
		std::string m_logDirectory="";
		std::unordered_map<std::string, FILE*> m_openFiles;
		std::vector<Logger*> m_loggers;
	};

}//end namespace