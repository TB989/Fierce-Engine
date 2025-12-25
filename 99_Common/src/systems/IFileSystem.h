#pragma once

#include "System.h"

#include <string>
#include <vector>

namespace Fierce {

	class IFileIO {
	protected:
		virtual bool openFile(std::string filename, std::string options) = 0;
		virtual void closeFile() = 0;
	};

	class IConsoleWriter {
	public:
		virtual ~IConsoleWriter() = default;
		virtual void print(const char* format, ...)=0;
		virtual void setColor(int color)=0;
	};

	class IBinaryFileReader{
	public:
		virtual ~IBinaryFileReader() = default;
		virtual bool openFile(std::string filename)=0;
		virtual bool readBinary(long* size, char** buffer)=0;
		virtual void closeFile()=0;
	};

	class IBinaryFileWriter {
	public:
		virtual ~IBinaryFileWriter() = default;
		virtual bool openFile(std::string filename)=0;
		virtual void closeFile()=0;
	};

	class ITextFileReader{
	public:
		virtual ~ITextFileReader() = default;
		virtual bool openFile(std::string filename)=0;
		virtual bool readNextLine(std::string& line)=0;
		virtual void closeFile()=0;
	};

	class ITextFileWriter {
	public:
		virtual ~ITextFileWriter() = default;
		virtual bool openFile(std::string filename)=0;
		virtual void print(const char* format, ...)=0;
		virtual void closeFile()=0;
	};

	class IFileSystem:public System{
	public:
		virtual ~IFileSystem() = default;

		virtual IConsoleWriter* createConsoleWriter()=0;
		virtual void deleteConsoleWriter(IConsoleWriter* writer)=0;

		virtual IBinaryFileReader* createBinaryFileReader(std::string directory)=0;
		virtual void deleteBinaryFileReader(IBinaryFileReader* reader)=0;

		virtual IBinaryFileWriter* createBinaryFileWriter(std::string directory)=0;
		virtual void deleteBinaryFileWriter(IBinaryFileWriter* writer)=0;

		virtual ITextFileReader* createTextFileReader(std::string directory)=0;
		virtual void deleteTextFileReader(ITextFileReader* reader)=0;

		virtual ITextFileWriter* createTextFileWriter(std::string directory)=0;
		virtual void deleteTextFileWriter(ITextFileWriter* writer)=0;

		virtual void getAllFileNames(std::string directory, std::vector<std::string>& filenames, std::string ending)=0;
	};

}