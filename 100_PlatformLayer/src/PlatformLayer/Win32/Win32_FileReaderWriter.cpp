#include "Win32_FileReaderWriter.h"

namespace Fierce {
	Win32_FileIO::Win32_FileIO(std::string directory) :FileIO(directory) {}

	bool Win32_FileIO::openFile(std::string filename,std::string options){
		//Close open file
		closeFile();

		//Check if directory and filename are set
		if (filename == "") {
			m_file = nullptr;
			return false;
		}

		//Concat directory and filename
		std::string path = m_directory;
		path.append(filename);

		m_file = fopen(path.c_str(), options.c_str());
		if (m_file == nullptr) {
			return false;
		}

		m_filename = filename;

		return true;
	}

	void Win32_FileIO::closeFile(){
		if (m_file != nullptr) {
			fclose(m_file);
			m_file = nullptr;
			m_filename = "";
		}
	}

	Win32_BinaryFileReader::Win32_BinaryFileReader(std::string directory) :Win32_FileIO(directory) {}

	Win32_BinaryFileReader::~Win32_BinaryFileReader(){}

	bool Win32_BinaryFileReader::openFile(std::string filename){
		return Win32_FileIO::openFile(filename,"rb");
	}

	bool Win32_BinaryFileReader::readBinary(long* size, char** buffer){
		//Check if there is an open file
		if (m_file == nullptr) {
			return false;
		}

		//Read size
		if (buffer == nullptr) {
			if (size == nullptr) {
				return false;
			}
			fseek(m_file, 0, SEEK_END);
			*size = ftell(m_file);
			fseek(m_file, 0, SEEK_SET);
		}
		//Read data
		else {
			if (*size <= 0) {
				return false;
			}
			size_t bytesRead = fread(*buffer, 1, *size, m_file);
			if (bytesRead != *size) {
				return false;
			}
		}

		return true;
	}

	void Win32_BinaryFileReader::closeFile(){
		Win32_FileIO::closeFile();
	}

	Win32_BinaryFileWriter::Win32_BinaryFileWriter(std::string directory) :Win32_FileIO(directory) {}

	Win32_BinaryFileWriter::~Win32_BinaryFileWriter(){}

	bool Win32_BinaryFileWriter::openFile(std::string filename){
		return Win32_FileIO::openFile(filename, "wb");
	}

	void Win32_BinaryFileWriter::closeFile(){
		Win32_FileIO::closeFile();
	}

	Win32_TextFileReader::Win32_TextFileReader(std::string directory) :Win32_FileIO(directory) {}

	Win32_TextFileReader::~Win32_TextFileReader(){}

	bool Win32_TextFileReader::openFile(std::string filename){
		return Win32_FileIO::openFile(filename, "r");
	}

	bool Win32_TextFileReader::readNextLine(std::string& line){
		char buffer[4096];
		if (fgets(buffer, sizeof(buffer), m_file)) {
			line = buffer;

			if (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
				line.erase(line.find_last_not_of("\r\n") + 1);
			}

			return true;
		}

		return false; 
	}

	void Win32_TextFileReader::closeFile(){
		Win32_FileIO::closeFile();
	}

	Win32_TextFileWriter::Win32_TextFileWriter(std::string directory) :Win32_FileIO(directory) {}

	Win32_TextFileWriter::~Win32_TextFileWriter(){}

	bool Win32_TextFileWriter::openFile(std::string filename){
		return Win32_FileIO::openFile(filename, "w");
	}

	void Win32_TextFileWriter::print(const char* format, ...){
		va_list args;
		va_start(args, format);
		vfprintf(m_file, format, args);
		fflush(m_file);
		va_end(args);
	}

	void Win32_TextFileWriter::closeFile(){
		Win32_FileIO::closeFile();
	}

	Win32_ConsoleWriter::Win32_ConsoleWriter(){
		m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	Win32_ConsoleWriter::~Win32_ConsoleWriter(){

	}

	void Win32_ConsoleWriter::print(const char* format, ...){
		va_list args;
		va_start(args, format);
		vfprintf(stdout, format,args);
		fflush(stdout);
		va_end(args);
	}

	void Win32_ConsoleWriter::setColor(int color){
		SetConsoleTextAttribute(m_handle, color);
	}
}