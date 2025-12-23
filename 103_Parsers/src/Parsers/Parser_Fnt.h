#pragma once

#include "src/systems/IFileSystem.h"
#include "src/utils/Font.h"

#include "Parser.h"

#include <vector>
#include <string>

namespace Fierce {

	class Parser_Fnt :public IParser_Fnt,public Parser {
	public:
		Parser_Fnt(IFileSystem* fileSystem, std::string directory);
		~Parser_Fnt();

		void parseFile(std::string filename, Font* font) override;

	private:
		void parseLine(std::string line, Font* font);
		void parseLineInfo(Font* font);
		void parseLineCommon(Font* font);
		void parseLinePage(Font* font);
		void parseLineChars(Font* font);
		void parseLineChar(Font* font);
		void parseLineKernings(Font* font);
		void parseLineKerning(Font* font);

	private:
		IFileSystem* m_fileSystem = nullptr;
		ITextFileReader* m_fileReader = nullptr;

		std::vector<std::string> m_lineParts;
		std::vector<std::string> m_tokens;
		int numKernings = 0;
	};

}//end namespace
