#pragma once

#include "Parser.h"

#include <string>

namespace Fierce {

	class Parser_Tex:public Parser{
	public:
		Parser_Tex(std::string directory);

		unsigned char* parseFile(std::string filename,int *width,int *height,int *numChannels);
		void freeData(unsigned char* pixels);

	private:
		std::string m_directory;
	};

}//end namespace