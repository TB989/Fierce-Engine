#pragma once

#include <string>

namespace Fierce {

	class Parser {
	public: 
		virtual ~Parser()=default;

	protected:
		bool isEmptyLine(std::string line);
		bool isCommentLine(std::string line);
		bool lineContains(std::string line, std::string token);

		int asInt(std::string value);
		std::string asString(std::string value);
		bool asBool(std::string value);
		int asArray(std::string value,int index);
	};
}