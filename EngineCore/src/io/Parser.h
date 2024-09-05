#pragma once

#include "src/FierceStrings.h"
#include <map>

namespace Fierce {

	class Parser {
	public:
		static std::map<std::string, std::string> parsePropertiesFile(std::string filename);
	};

}//end namespace