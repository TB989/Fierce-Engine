#pragma once

#include "Parser.h"

#include <string>

namespace Fierce {

	class Parser_Tex:public IParser_Tex,public Parser {
	public:
		Parser_Tex(std::string directory);

		unsigned char* parseFile(std::string filename,int *width,int *height,int *numChannels) override;
		void freeData(unsigned char* pixels) override;

	private:
		std::string m_directory;
	};

}//end namespace