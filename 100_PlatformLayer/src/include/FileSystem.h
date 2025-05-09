#pragma once

#include <string>

#include "src/utils/System.h"

namespace Fierce {

	class FileIO {
	public:
		FileIO(std::string directory) {
			m_directory = directory;
		}

	protected:
		virtual bool openFile(std::string filename, std::string options) = 0;
		virtual void closeFile() = 0;

		std::string m_directory="";
		std::string m_filename = "";
	};

	class ConsoleWriter {
	public:
		ConsoleWriter() {};

		virtual void print(const char* format, ...) = 0;
		virtual void setColor(int color)=0;
	};

	class BinaryFileReader{
	public:
		~BinaryFileReader() {};

		virtual bool openFile(std::string filename) = 0;
		virtual bool readBinary(long* size, char** buffer)=0;
		virtual void closeFile() = 0;
	};

	class BinaryFileWriter {
	public:
		~BinaryFileWriter() {};

		virtual bool openFile(std::string filename) = 0;
		virtual void closeFile() = 0;
	};

	class TextFileReader{
	public:
		~TextFileReader() {};

		virtual bool openFile(std::string filename) = 0;
		virtual void closeFile() = 0;
	};

	class TextFileWriter {
	public:
		~TextFileWriter() {};

		virtual bool openFile(std::string filename) = 0;
		virtual void print(const char* format, ...) =0;
		virtual void closeFile() = 0;
	};

	class FileSystem :public System {
	public:
		virtual ConsoleWriter* createConsoleWriter() = 0;
		virtual void deleteConsoleWriter(ConsoleWriter* writer) = 0;

		virtual BinaryFileReader* createBinaryFileReader(std::string directory) = 0;
		virtual void deleteBinaryFileReader(BinaryFileReader* reader) = 0;

		virtual BinaryFileWriter* createBinaryFileWriter(std::string directory) = 0;
		virtual void deleteBinaryFileWriter(BinaryFileWriter* writer) = 0;

		virtual TextFileReader* createTextFileReader(std::string directory) = 0;
		virtual void deleteTextFileReader(TextFileReader* reader) = 0;

		virtual TextFileWriter* createTextFileWriter(std::string directory) = 0;
		virtual void deleteTextFileWriter(TextFileWriter* writer) = 0;
	};

}