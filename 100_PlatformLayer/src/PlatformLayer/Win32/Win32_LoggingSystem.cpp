#include "Win32_LoggingSystem.h"

#include "Win32_Logger.h"

#include "time.h"
#include <filesystem>

namespace Fierce {

	Win32_LoggingSystem::Win32_LoggingSystem(){
		m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void Win32_LoggingSystem::initSystem(std::string m_assetDirectory){
		m_logDirectory = m_assetDirectory;
		m_logDirectory.append("logs/");
		m_logger = createLogger("LOG", true, "ALL_LOGS");
		m_logger->info("Init logging system");
	}

	void Win32_LoggingSystem::linkSystem(System* system){
		if (dynamic_cast<ITimeDateSystem*>(system)) {
			m_timeDateSystem = (ITimeDateSystem*)system;
		}
		else if (dynamic_cast<IFileSystem*>(system)) {
			m_fileSystem = (IFileSystem*)system;
		}
	}

	void Win32_LoggingSystem::updateSystem(){
		for (ILogger* logger:m_loggers) {
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
		if (m_logger != nullptr) {
			m_logger->info("Clean up logging system");
			deleteLogger(m_logger);
		}

		for (auto pair : m_openFiles) {
			pair.second->closeFile();
		}
	}

	std::string Win32_LoggingSystem::getName(){
		return "LoggingSystem";
	}

	ILogger* Win32_LoggingSystem::createLogger(std::string name){
		ILogger* logger = new Win32_Logger(name, nullptr,m_fileSystem->createConsoleWriter());
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

	ILogger* Win32_LoggingSystem::createLogger(std::string name, bool logToConsole, std::string file){
		int counter = 1;

		while (true) {
			//Create full file path
			std::string temporaryFileName = "";
			temporaryFileName.append(std::to_string(m_timeDateSystem->getDay()))
				.append("_")
				.append(std::to_string(m_timeDateSystem->getMonth()))
				.append("_")
				.append(std::to_string(m_timeDateSystem->getYear()))
				.append("_")
				.append(file);

			//Create temporary filename
			temporaryFileName.append("_").append(std::to_string(counter)).append(".log");
			
			//Another logger already writes in this file
			if (m_openFiles.find(temporaryFileName) != m_openFiles.end()) {
				ITextFileWriter* writer= m_openFiles[temporaryFileName];
				ILogger* logger= new Win32_Logger(name,writer,logToConsole? m_fileSystem->createConsoleWriter() :nullptr);
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
			std::string fullPath = m_logDirectory;
			fullPath.append(temporaryFileName);
			if (std::filesystem::exists(fullPath)) {
				counter++;
			}

			//File does not exist and no other logger writes into the file
			else {
				ITextFileWriter* writer = m_fileSystem->createTextFileWriter(m_logDirectory);
				writer->openFile(temporaryFileName);
				m_openFiles[temporaryFileName] = writer;
				ILogger* logger = new Win32_Logger(name, writer, logToConsole ? m_fileSystem->createConsoleWriter() : nullptr);
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

	void Win32_LoggingSystem::deleteLogger(ILogger* logger){
		auto it = std::remove(m_loggers.begin(), m_loggers.end(), logger);
		if (it != m_loggers.end()) {
			m_loggers.erase(it, m_loggers.end());
		}
		delete logger;
	}

}//end namespace