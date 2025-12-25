#include "Parser_Ini.h"

#include "src/utils/FierceStrings.h"

#define KEY m_tokens[0]
#define VALUE m_tokens[1]

namespace Fierce {
	Parser_Ini::Parser_Ini(IFileSystem* fileSystem, std::string directory){
		m_fileSystem = fileSystem;
		m_fileReader = fileSystem->createTextFileReader(directory);
	}

	Parser_Ini::~Parser_Ini(){
		m_fileSystem->deleteTextFileReader(m_fileReader);
	}

	void Parser_Ini::parseFile(std::string filename, EngineSettings& settings) {
		m_fileReader->openFile(filename);

		std::string line;
		while (m_fileReader->readNextLine(line)) {
			trim(line);

			//Empty line
			if (isEmptyLine(line)) continue;

			//Comment starts with //
			if (isCommentLine(line)) continue;

			//Invalid line without =
			if (!lineContains(line, "=")) continue;

			//Valid line
			parseLine(line, settings);
		}

		m_fileReader->closeFile();
	}

	void Parser_Ini::parseLine(std::string line, EngineSettings& settings) {
		m_tokens = split(line, '=');
		trim(KEY);
		trim(VALUE);
		
		if (KEY == "windowMode" || KEY == "WINDOW_MODE") {
			if (VALUE == "windowed" || VALUE == "WINDOWED") {
				settings.windowMode = WINDOW_MODE::WINDOWED;
			}
			if (VALUE == "fullscreen" || VALUE == "FULLSCREEN") {
				settings.windowMode = WINDOW_MODE::FULLSCREEN;
			}
		}
		if (KEY == "width" || KEY == "WIDTH") {
			settings.width = asInt(VALUE);
		}
		if (KEY == "height" || KEY == "HEIGHT") {
			settings.height = asInt(VALUE);
		}
		if (KEY == "assetPath" || KEY == "ASSETPATH") {
			settings.assetPath = VALUE;
		}
		if (KEY == "app" || KEY == "APP") {
			settings.app = VALUE;
		}
	}
}