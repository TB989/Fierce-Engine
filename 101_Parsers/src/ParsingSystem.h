#pragma once

#include "Parser.h"
#include "Parser_Fnt.h"
#include "Parser_Ini.h"
#include "Parser_Tex.h"

#include "src/utils/System.h"
#include "src/include/LoggingSystem.h"
#include "src/include/FileSystem.h"

#include <vector>
#include <string>

namespace Fierce {

	class ParsingSystem : public System{
	public:
		ParsingSystem();
		~ParsingSystem();

		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		Parser_Fnt* createParser_Fnt(std::string directory);
		Parser_Ini* createParser_Ini(std::string directory);
		Parser_Tex* createParser_Tex(std::string directory);
		void deleteParser(Parser* parser);

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		FileSystem* m_fileSystem = nullptr;

		std::vector<Parser*> m_parsers;
	};
}
