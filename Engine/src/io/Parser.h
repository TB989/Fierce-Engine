#pragma once

#include "src/Common.h"

class Parser {
public:
	static std::map<std::string, std::string> parsePropertiesFile(std::string filename);

	static std::vector<char> readBinary(std::string filename);
	static std::vector<char> readText(std::string filename);
};