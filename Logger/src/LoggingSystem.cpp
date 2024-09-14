#include "LoggingSystem.h"

namespace Fierce {

	LoggingSystem::LoggingSystem(std::string logDirectory){
		m_logDirectory = logDirectory;
	}

	LoggingSystem::~LoggingSystem(){}

	void LoggingSystem::initSystem(){
		m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void LoggingSystem::updateSystem(){}

	void LoggingSystem::cleanUpSystem(){
		for (auto pair : m_openFiles) {
			fclose(pair.second);
		}
	}

	Logger* LoggingSystem::createLogger(std::string name){
		Logger* logger = new Logger(name, m_handle, true, false, NULL);
		m_loggers.push_back(logger);
		return logger;
	}

	Logger* LoggingSystem::createLogger(std::string name, bool logToConsole, std::string file){
		//Create full file path
		time_t now = time(0);
		tm* ltm = localtime(&now);
		std::string fullPath = m_logDirectory;
		fullPath.append(std::to_string(1900 + ltm->tm_year))
			.append("_")
			.append(std::to_string(1 + ltm->tm_mon))
			.append("_")
			.append(std::to_string(ltm->tm_mday))
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
				Logger* logger= new Logger(name,m_handle,logToConsole,true,stream);
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
				Logger* logger = new Logger(name, m_handle, logToConsole, true, stream);
				m_loggers.push_back(logger);
				return logger;
			}
		}
	}

	void LoggingSystem::deleteLogger(Logger* logger){
		auto it = std::remove(m_loggers.begin(), m_loggers.end(), logger);
		if (it != m_loggers.end()) {
			m_loggers.erase(it, m_loggers.end());
		}
		delete logger;
	}

}//end namespace