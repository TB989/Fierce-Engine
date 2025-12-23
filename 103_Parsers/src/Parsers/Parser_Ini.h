#pragma once

#include "src/systems/IFileSystem.h"
#include "src/utils/EngineSettings.h"

#include "Parser.h"

#include <vector>
#include <string>

namespace Fierce {

	class Parser_Ini :public IParser_Ini, public Parser {
	public:
		Parser_Ini(IFileSystem* fileSystem, std::string directory);
		~Parser_Ini();

		void parseFile(std::string filename, EngineSettings& settings) override;

	private:
		void parseLine(std::string line, EngineSettings& settings);

	private:
		IFileSystem* m_fileSystem = nullptr;
		ITextFileReader* m_fileReader=nullptr;

		std::vector<std::string> m_tokens;
	};

}//end namespace

