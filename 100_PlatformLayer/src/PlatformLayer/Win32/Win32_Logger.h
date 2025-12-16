#pragma once

#include "Windows.h"

#include "src/systems/ILoggingSystem.h"
#include "src/systems/IFileSystem.h"

namespace Fierce {

	class Win32_Logger:public ILogger {
	public:
		Win32_Logger(std::string name, ITextFileWriter* fileWriter, IConsoleWriter* consoleWriter);

		void log(const char* logLevel, const char* format, ...) override;
		void info(const char* format, ...) override;
		void warn(const char* format, ...) override;
		void error(const char* format, ...) override;
	
		void update(int year,int month,int day,int hours,int minutes,int seconds) override;

		virtual void setConsoleUseColors(bool useColors) override;
		virtual void setConsolePrintName(bool printName) override;
		virtual void setConsolePrintLogLevel(bool printLogLevel) override;
		virtual void setConsolePrintDate(bool printDate) override;
		virtual void setConsolePrintTime(bool printTime) override;

		virtual void setFilePrintName(bool printName) override;
		virtual void setFilePrintLogLevel(bool printLogLevel) override;
		virtual void setFilePrintDate(bool printDate) override;
		virtual void setFilePrintTime(bool printTime) override;

	private:
		ITextFileWriter* m_fileWriter=nullptr;
		IConsoleWriter* m_consoleWriter=nullptr;

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

		std::string m_name = "";

		//Console
		bool m_c_useColors = true;
		bool m_c_printName = true;
		bool m_c_printLogLevel = false;
		bool m_c_printDate = false;
		bool m_c_printTime = true;

		//File
		bool m_f_printName = true;
		bool m_f_printLogLevel = true;
		bool m_f_printDate = false;
		bool m_f_printTime = true;
	};

}//end namespace