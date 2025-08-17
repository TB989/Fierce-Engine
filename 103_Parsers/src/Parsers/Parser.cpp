#include "Parser.h"

#include "src/PlatformLayer/utils/FierceStrings.h"

namespace Fierce {

	bool Parser::isEmptyLine(std::string line){
		return line.empty();
	}

	bool Parser::isCommentLine(std::string line){
		return startsWith(line,"//");
	}

	bool Parser::lineContains(std::string line, std::string token){
		return contains(line,token);
	}

	int Parser::asInt(std::string value){
		return std::stoi(value);
	}

	std::string Parser::asString(std::string value){
		return value.substr(1, value.size() - 2);
	}

	bool Parser::asBool(std::string value){
		if (value == "0") {
			return false;
		}
		else {
			return true;
		}
	}

	int Parser::asArray(std::string value, int index){
		std::vector<std::string> parts= split(value, ',');
		trim(parts[index]);
		return asInt(parts[index]);
	}
}