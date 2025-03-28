#pragma once

#include "src/FierceStrings.h"
#include <unordered_map>
#include <Windows.h>

namespace Fierce {

	class Logger {
	public:
		Logger(std::string name, HANDLE handle, bool logToConsole, bool logToFile, FILE* stream);

		void log(const char* logLevel, const char* format, ...);
		void info(const char* format, ...);
		void warn(const char* format, ...);
		void error(const char* format, ...);

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

	private:
		std::string m_name;
		HANDLE m_handle;
		FILE* m_stream = NULL;

		bool m_logToFile;
		bool m_logToConsole;

		//Console
		bool m_c_useColors;
		bool m_c_printName;
		bool m_c_printLogLevel;
		bool m_c_printDate;
		bool m_c_printTime;

		//File
		bool m_f_printName;
		bool m_f_printLogLevel;
		bool m_f_printDate;
		bool m_f_printTime;
	};

}//end namespace