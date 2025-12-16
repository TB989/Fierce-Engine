#pragma once

#include <vector>
#include <unordered_map>

#include "Windows.h"

#include "src/systems/ILoggingSystem.h"
#include "src/systems/ITimeDateSystem.h"
#include "src/systems/IFileSystem.h"

namespace Fierce {

	class Win32_LoggingSystem:public ILoggingSystem{
	public:
		Win32_LoggingSystem();

		void initSystem(std::string m_assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		std::string getName() override;

		ILogger* createLogger(std::string name) override;
		ILogger* createLogger(std::string name,bool logToConsole, std::string file) override;
		void deleteLogger(ILogger* logger) override;

	private:
		std::string m_logDirectory = "";

		ITimeDateSystem* m_timeDateSystem = nullptr;
		IFileSystem* m_fileSystem = nullptr;

		ILogger* m_logger = nullptr;

		HANDLE m_handle=NULL;
		std::unordered_map<std::string, ITextFileWriter*> m_openFiles;
		std::vector<ILogger*> m_loggers;
	};

}//end namespace