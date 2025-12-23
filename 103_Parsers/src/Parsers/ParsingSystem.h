#pragma once

#include "Parser.h"
#include "Parser_Fnt.h"
#include "Parser_Ini.h"
#include "Parser_Tex.h"

#include "src/systems/IParsingSystem.h"
#include "src/systems/ILoggingSystem.h"
#include "src/systems/IFileSystem.h"

#include <vector>
#include <string>

namespace Fierce {

	class ParsingSystem : public IParsingSystem{
	public:
		ParsingSystem();
		~ParsingSystem();

		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		std::string getName() override;

		IParser_Fnt* createParser_Fnt(std::string directory) override;
		IParser_Ini* createParser_Ini(std::string directory) override;
		IParser_Tex* createParser_Tex(std::string directory) override;
		void deleteParser(IParser* parser) override;

	private:
		ILoggingSystem* m_loggingSystem = nullptr;
		ILogger* m_logger = nullptr;

		IFileSystem* m_fileSystem = nullptr;

		std::vector<IParser*> m_parsers;
	};
}
