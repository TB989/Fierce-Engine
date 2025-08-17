#include "ParsingSystem.h"

namespace Fierce {

	ParsingSystem::ParsingSystem(){

	}

	ParsingSystem::~ParsingSystem(){

	}

	void ParsingSystem::initSystem(std::string assetDirectory){
		if (m_loggingSystem != nullptr) {
			m_logger = m_loggingSystem->createLogger("PARSER", true, "IO");
			m_logger->info("Init parsing system");
		}
	}

	void ParsingSystem::linkSystem(System* system){
		if (dynamic_cast<LoggingSystem*>(system)) {
			m_loggingSystem = (LoggingSystem*)system;
		}
		if (dynamic_cast<FileSystem*>(system)) {
			m_fileSystem = (FileSystem*)system;
		}
	}

	void ParsingSystem::updateSystem(){

	}

	void ParsingSystem::cleanUpSystem(){
		if (m_logger != nullptr) {
			m_logger->info("Clean up parsing system");
			m_loggingSystem->deleteLogger(m_logger);
		}
	}

	Parser_Fnt* ParsingSystem::createParser_Fnt(std::string directory){
		Parser_Fnt* parser = new Parser_Fnt(m_fileSystem,directory);
		m_parsers.push_back(parser);
		return parser;
	}

	Parser_Ini* ParsingSystem::createParser_Ini(std::string directory) {
		Parser_Ini* parser = new Parser_Ini(m_fileSystem,directory);
		m_parsers.push_back(parser);
		return parser;
	}

	Parser_Tex* ParsingSystem::createParser_Tex(std::string directory) {
		Parser_Tex* parser = new Parser_Tex(directory);
		m_parsers.push_back(parser);
		return parser;
	}

	void ParsingSystem::deleteParser(Parser* parser){
		auto it = std::find(m_parsers.begin(), m_parsers.end(), parser);
		if (it != m_parsers.end()) {
			m_parsers.erase(it);
			delete parser;
		}
	}
};