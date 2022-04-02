#pragma once

#include "utils/FierceStrings.h"
#include <map>

class Parser {
public:
	static std::map<std::string, std::string> parsePropertiesFile(std::string filename);
};