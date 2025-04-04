#pragma once

#include "Windows.h"

#include "src/include/LoggingSystem.h"

namespace Fierce {

	class Win32_Logger:public Logger {
	public:
		Win32_Logger(std::string name, HANDLE handle, bool logToConsole, bool logToFile, FILE* stream);

		void log(const char* logLevel, const char* format, ...) override;
		void info(const char* format, ...) override;
		void warn(const char* format, ...) override;
		void error(const char* format, ...) override;
	
		void update(int year,int month,int day,int hours,int minutes,int seconds) override;

	private:
		HANDLE m_handle;
		FILE* m_stream = NULL;

		int m_year = -1;
		int m_month = -1;
		int m_day = -1;

		int m_hours = -1;
		int m_minutes = -1;
		int m_seconds = -1;
	};

}//end namespace