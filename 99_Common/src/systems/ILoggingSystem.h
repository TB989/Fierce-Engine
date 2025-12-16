#pragma once

#include "System.h"

#include <string>

namespace Fierce {

	class ILogger {
	public:
		virtual void log(const char* logLevel, const char* format, ...)=0;
		virtual void info(const char* format, ...)=0;
		virtual void warn(const char* format, ...)=0;
		virtual void error(const char* format, ...)=0;

	public:
		virtual void setConsoleUseColors(bool useColors)=0;
		virtual void setConsolePrintName(bool printName)=0;
		virtual void setConsolePrintLogLevel(bool printLogLevel)=0;
		virtual void setConsolePrintDate(bool printDate)=0;
		virtual void setConsolePrintTime(bool printTime)=0;

		virtual void setFilePrintName(bool printName)=0;
		virtual void setFilePrintLogLevel(bool printLogLevel)=0;
		virtual void setFilePrintDate(bool printDate)=0;
		virtual void setFilePrintTime(bool printTime)=0;

		virtual void update(int year, int month, int day, int hours, int minutes, int seconds)=0;
	};

	class ILoggingSystem:public System{
	public:
		virtual ILogger* createLogger(std::string name)=0;
		virtual ILogger* createLogger(std::string name, bool logToConsole, std::string file)=0;
		virtual void deleteLogger(ILogger* logger)=0;
	};

};
