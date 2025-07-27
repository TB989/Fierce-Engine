#pragma once

#include "src/include/FileSystem.h"

#include "Parser.h"

namespace Fierce {

	class Parser_Spv {
	public:
		Parser_Spv(BinaryFileReader* binaryFileReader);

		void parseFile(std::string filename, long* size, char* sourcecode);

	private:
		BinaryFileReader* m_fileReader = nullptr;
	};

}//end namespace