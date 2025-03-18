#pragma once

#include "src/FierceStrings.h"
#include <map>
#include "src/font/Font.h"

namespace Fierce {

	class Parser {
	public:
		static std::map<std::string, std::string> parsePropertiesFile(std::string filename);
		static Font* parseFontFile(std::string filename);
	};

}//end namespace