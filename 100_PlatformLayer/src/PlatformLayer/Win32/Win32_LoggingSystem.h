#pragma once

#include <vector>
#include <unordered_map>

#include "Windows.h"

#include "src/PlatformLayer/include/LoggingSystem.h"
#include "src/systems/ITimeDateSystem.h"
#include "src/PlatformLayer/include/FileSystem.h"

namespace Fierce {

	class Win32_LoggingSystem:public LoggingSystem {
	public:
		Win32_LoggingSystem();

		void initSystem(std::string m_assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Logger* createLogger(std::string name) override;
		Logger* createLogger(std::string name,bool logToConsole, std::string file) override;
		void deleteLogger(Logger* logger) override;

	private:
		ITimeDateSystem* m_timeDateSystem = nullptr;
		FileSystem* m_fileSystem = nullptr;

		HANDLE m_handle=NULL;
		std::unordered_map<std::string, TextFileWriter*> m_openFiles;
		std::vector<Logger*> m_loggers;
	};

}//end namespace