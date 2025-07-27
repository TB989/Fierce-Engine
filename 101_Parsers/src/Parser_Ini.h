#pragma once

#include "src/include/FileSystem.h"

#include "src/utils/EngineSettings.h"

#include "Parser.h"

#include <vector>
#include <string>

namespace Fierce {

	class Parser_Ini :public Parser {
	public:
		Parser_Ini(TextFileReader* textFileReader);

		void parseFile(std::string filename, EngineSettings& settings);

	private:
		void parseLine(std::string line, EngineSettings& settings);

	private:
		TextFileReader* m_fileReader=nullptr;
		std::vector<std::string> m_tokens;
	};

}//end namespace

