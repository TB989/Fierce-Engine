#include "FileReader.h"

#include "string.h"

namespace Fierce {
	bool FileReader::openFile(const char* filename){
		//Close open file
		closeFile();

		//Check if directory and filename are set
		if (m_directory == nullptr || filename == nullptr) {
			m_file = nullptr;
			return false;
		}

		//Concat directory and filename
		char* path = nullptr;
		int pathSize = strlen(m_directory)+strlen(filename)+1;
		path = new char[pathSize];
		strcpy(path, m_directory);
		strcat(path, filename);

		//Open file
		m_file = fopen(path,"rb");
		if (m_file == nullptr) {
			return false;
		}

		return true;
	}
	void FileReader::closeFile(){
		if (m_file != nullptr) {
			fclose(m_file);
		}
	}

	bool FileReader::readBinary(long* size, char** buffer){
		//Check if there is an open file
		if (m_file == nullptr) {
			return false;
		}

		//Read size
		if (buffer==nullptr) {
			if (size==nullptr) {
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
}