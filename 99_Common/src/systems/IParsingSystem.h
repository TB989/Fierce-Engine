#pragma once

#include "System.h"

#include "../utils/Font.h"
#include "../utils/EngineSettings.h"

namespace Fierce {

	class IParser {
	public :
		virtual ~IParser()=default;
	};

	class IParser_Fnt:public IParser {
	public:
		virtual ~IParser_Fnt() = default;
		virtual void parseFile(std::string filename, Font* font)=0;
	};

	class IParser_Ini:public IParser {
	public:
		virtual ~IParser_Ini() = default;
		virtual void parseFile(std::string filename, EngineSettings& settings) = 0;
	};

	class IParser_Tex:public IParser {
	public:
		virtual ~IParser_Tex() = default;
		virtual unsigned char* parseFile(std::string filename, int* width, int* height, int* numChannels)=0;
		virtual void freeData(unsigned char* pixels)=0;
	};

	class IParsingSystem :public System {
	public:
		virtual ~IParsingSystem() = default;
		virtual IParser_Fnt* createParser_Fnt(std::string directory)=0;
		virtual IParser_Ini* createParser_Ini(std::string directory)=0;
		virtual IParser_Tex* createParser_Tex(std::string directory)=0;
		virtual void deleteParser(IParser* parser)=0;
	};
}
