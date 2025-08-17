#pragma once

#include <string>

#include "src/PlatformLayer/utils/System.h"

namespace Fierce {

	class Logger {
	public:
		Logger(std::string name) {
			m_name = name;
		}

		virtual void log(const char* logLevel, const char* format, ...)=0;
		virtual void info(const char* format, ...)=0;
		virtual void warn(const char* format, ...)=0;
		virtual void error(const char* format, ...)=0;

	public:
		void setConsoleUseColors(bool useColors) { m_c_useColors = useColors; }
		void setConsolePrintName(bool printName) { m_c_printName = printName; }
		void setConsolePrintLogLevel(bool printLogLevel) { m_c_printLogLevel = printLogLevel; }
		void setConsolePrintDate(bool printDate) { m_c_printDate = printDate; }
		void setConsolePrintTime(bool printTime) { m_c_printTime = printTime; }

		void setFilePrintName(bool printName) { m_f_printName = printName; }
		void setFilePrintLogLevel(bool printLogLevel) { m_f_printLogLevel = printLogLevel; }
		void setFilePrintDate(bool printDate) { m_f_printDate = printDate; }
		void setFilePrintTime(bool printTime) { m_f_printTime = printTime; }

		virtual void update(int year, int month, int day, int hours, int minutes, int seconds)=0;

	protected:
		std::string m_name="";

		//Console
		bool m_c_useColors=true;
		bool m_c_printName=true;
		bool m_c_printLogLevel=false;
		bool m_c_printDate=false;
		bool m_c_printTime=true;

		//File
		bool m_f_printName=true;
		bool m_f_printLogLevel=true;
		bool m_f_printDate=false;
		bool m_f_printTime=true;
	};

	class LoggingSystem :public System {
	public:
		virtual Logger* createLogger(std::string name)=0;
		virtual Logger* createLogger(std::string name, bool logToConsole, std::string file)=0;
		virtual void deleteLogger(Logger* logger)=0;

	protected:
		std::string m_logDirectory = "";
	};

};
