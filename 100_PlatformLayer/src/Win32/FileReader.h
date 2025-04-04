#pragma once

#include <stdio.h>

namespace Fierce {

	class FileReader {
	public:

		void setDirectory(const char* directory) { m_directory = directory; }

		bool openFile(const char* filename);
		void closeFile();

		bool readBinary(long* size,char** buffer);

	private:
		const char* m_directory=nullptr;
		FILE* m_file = nullptr;
	};
}