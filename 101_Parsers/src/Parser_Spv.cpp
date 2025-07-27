#include "Parser_Spv.h"

namespace Fierce {
	Fierce::Parser_Spv::Parser_Spv(BinaryFileReader* binaryFileReader){
		m_fileReader = binaryFileReader;
	}

	void Parser_Spv::parseFile(std::string filename, long* size, char* sourceCode){
		m_fileReader->openFile(filename);
		m_fileReader->readBinary(size, &sourceCode);
		m_fileReader->closeFile();
	}
}