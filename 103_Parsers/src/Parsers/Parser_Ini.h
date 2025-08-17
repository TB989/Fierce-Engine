#pragma once

#include "src/PlatformLayer/include/FileSystem.h"

#include "src/PlatformLayer/utils/EngineSettings.h"

#include "Parser.h"

#include <vector>
#include <string>

namespace Fierce {

	class Parser_Ini :public Parser {
	public:
		Parser_Ini(FileSystem* fileSystem, std::string directory);
		~Parser_Ini();

		void parseFile(std::string filename, EngineSettings& settings);

	private:
		void parseLine(std::string line, EngineSettings& settings);

	private:
		FileSystem* m_fileSystem = nullptr;
		TextFileReader* m_fileReader=nullptr;

		std::vector<std::string> m_tokens;
	};

}//end namespace

