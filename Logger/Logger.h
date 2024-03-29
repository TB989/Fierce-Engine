#pragma once

#include <Windows.h>
#include <string>

class Logger {
public:
	Logger(std::string name);

	void log(const char* type, const char* text, ...);
	void info(const char* text, ...);
	void warn(const char* text, ...);
	void error(const char* text, ...);

	static void setPrintName(bool option) { printName = option; }
	static void setPrintType(bool option) { printType = option; }
	static void setUseColors(bool option) { useColors = option; }
	static void setPrintDate(bool option) { printDate = option; }
	static void setPrintTime(bool option) { printTime = option; }
private:
	static HANDLE handle;
	std::string m_name;

	static bool useColors;
	static bool printName;
	static bool printType;
	static bool printDate;
	static bool printTime;
};