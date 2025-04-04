#include "Win32_LoggingSystem.h"

#include "Win32_Logger.h"

#include "src/Win32/Win32_TimeDateSystem.h"

#include "time.h"
#include <filesystem>

namespace Fierce {

	Win32_LoggingSystem::Win32_LoggingSystem(TimeDateSystem* timeDateSystem){
		m_timeDateSystem = timeDateSystem;
	}

	void Win32_LoggingSystem::initSystem(){
		m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void Win32_LoggingSystem::updateSystem(){
		for (Logger* logger:m_loggers) {
			logger->update(
				m_timeDateSystem->getYear(),
				m_timeDateSystem->getMonth(),
				m_timeDateSystem->getDay(),
				m_timeDateSystem->getHours(),
				m_timeDateSystem->getMinutes(),
				m_timeDateSystem->getSeconds());
		}
	}

	void Win32_LoggingSystem::cleanUpSystem(){
		for (auto pair : m_openFiles) {
			fclose(pair.second);
		}
	}

	Logger* Win32_LoggingSystem::createLogger(std::string name){
		Logger* logger = new Win32_Logger(name, m_handle, true, false, NULL);
		logger->update(
			m_timeDateSystem->getYear(),
			m_timeDateSystem->getMonth(),
			m_timeDateSystem->getDay(),
			m_timeDateSystem->getHours(),
			m_timeDateSystem->getMinutes(),
			m_timeDateSystem->getSeconds());
		m_loggers.push_back(logger);
		return logger;
	}

	Logger* Win32_LoggingSystem::createLogger(std::string name, bool logToConsole, std::string file){
		//Create full file path
		std::string fullPath = m_logDirectory;
		fullPath.append(std::to_string(m_timeDateSystem->getYear()))
			.append("_")
			.append(std::to_string(m_timeDateSystem->getYear()))
			.append("_")
			.append(std::to_string(m_timeDateSystem->getYear()))
			.append("_")
			.append(file);

		std::string temporaryFileName;
		int counter = 1;

		while (true) {
			//Create temporary filename
			temporaryFileName = fullPath;
			temporaryFileName.append("_").append(std::to_string(counter)).append(".log");
			
			//Another logger already writes in this file
			if (m_openFiles.find(temporaryFileName) != m_openFiles.end()) {
				FILE* stream = m_openFiles[temporaryFileName];
				Logger* logger= new Win32_Logger(name,m_handle,logToConsole,true,stream);
				logger->update(
					m_timeDateSystem->getYear(),
					m_timeDateSystem->getMonth(),
					m_timeDateSystem->getDay(),
					m_timeDateSystem->getHours(),
					m_timeDateSystem->getMinutes(),
					m_timeDateSystem->getSeconds());
				m_loggers.push_back(logger);
				return logger;
			}

			//No logger writes into this file, but it exists
			if (std::filesystem::exists(temporaryFileName)) {
				counter++;
			}

			//File does not exist and no other logger writes into the file
			else {
				FILE* stream = fopen(temporaryFileName.c_str(), "w");
				m_openFiles[temporaryFileName] = stream;
				Logger* logger = new Win32_Logger(name, m_handle, logToConsole, true, stream);
				logger->update(
					m_timeDateSystem->getYear(),
					m_timeDateSystem->getMonth(),
					m_timeDateSystem->getDay(),
					m_timeDateSystem->getHours(),
					m_timeDateSystem->getMinutes(),
					m_timeDateSystem->getSeconds());
				m_loggers.push_back(logger);
				return logger;
			}
		}
	}

	void Win32_LoggingSystem::deleteLogger(Logger* logger){
		auto it = std::remove(m_loggers.begin(), m_loggers.end(), logger);
		if (it != m_loggers.end()) {
			m_loggers.erase(it, m_loggers.end());
		}
		delete logger;
	}

}//end namespace