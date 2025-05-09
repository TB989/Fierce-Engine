#pragma once

#include "Windows.h"

#include "src/include/LoggingSystem.h"
#include "src/include/FileSystem.h"

namespace Fierce {

	class Win32_Logger:public Logger {
	public:
		Win32_Logger(std::string name, TextFileWriter* fileWriter, ConsoleWriter* consoleWriter);

		void log(const char* logLevel, const char* format, ...) override;
		void info(const char* format, ...) override;
		void warn(const char* format, ...) override;
		void error(const char* format, ...) override;
	
		void update(int year,int month,int day,int hours,int minutes,int seconds) override;

	private:
		TextFileWriter* m_fileWriter=nullptr;
		ConsoleWriter* m_consoleWriter=nullptr;

		int m_year = -1;
		int m_month = -1;
		int m_day = -1;

		int m_hours = -1;
		int m_minutes = -1;
		int m_seconds = -1;

		char m_messageBuffer[1024];
		char m_dateBuffer[20];
		char m_timeBuffer[20];
		char m_nameBuffer[50];

		const char* m_logLevelInfo = "[INFO]";
		const char* m_logLevelWarn = "[WARN]";
		const char* m_logLevelError = "[ERROR]";
	};

}//end namespace