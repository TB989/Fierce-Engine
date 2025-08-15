#include "Win32_FileSystem.h"

#include "src/Win32/Win32_LoggingSystem.h"

#include "Win32_FileReaderWriter.h"

#include <filesystem>

#include "src/utils/FierceStrings.h"

namespace Fierce {
	Win32_FileSystem::Win32_FileSystem(){
		
	}

	Win32_FileSystem::~Win32_FileSystem(){
		for (BinaryFileReader* reader : m_binaryReaders) {
			delete reader;
		}
		for (TextFileReader* reader : m_textReaders) {
			delete reader;
		}
	}

	void Win32_FileSystem::initSystem(std::string m_assetDirectory) {
		if (m_loggingSystem!=nullptr) {
			m_logger = m_loggingSystem->createLogger("FILE",true,"IO");
			m_logger->info("Init file system");
		}
	}

	void Win32_FileSystem::linkSystem(System* system){
		if (dynamic_cast<LoggingSystem*>(system)) {
			m_loggingSystem = (LoggingSystem*)system;
		}
	}

	void Win32_FileSystem::updateSystem() {
		
	}

	void Win32_FileSystem::cleanUpSystem() {
		if (m_logger!=nullptr) {
			m_logger->info("Clean up file system");
			m_loggingSystem->deleteLogger(m_logger);
		}
	}

	ConsoleWriter* Win32_FileSystem::createConsoleWriter(){
		if (m_consoleWriter==nullptr) {
			m_consoleWriter = new Win32_ConsoleWriter();
		}
		return m_consoleWriter;
	}

	void Win32_FileSystem::deleteConsoleWriter(ConsoleWriter* writer){

	}

	BinaryFileReader* Win32_FileSystem::createBinaryFileReader(std::string directory) {
		BinaryFileReader* reader = new Win32_BinaryFileReader(directory);
		m_binaryReaders.push_back(reader);
		return reader;
	}

	void Win32_FileSystem::deleteBinaryFileReader(BinaryFileReader* reader) {
		auto it = std::find(m_binaryReaders.begin(), m_binaryReaders.end(), reader);
		if (it != m_binaryReaders.end()) {
			m_binaryReaders.erase(it);
			//delete reader;
		}
	}

	BinaryFileWriter* Win32_FileSystem::createBinaryFileWriter(std::string directory) {
		BinaryFileWriter* writer = new Win32_BinaryFileWriter(directory);
		m_binaryWriters.push_back(writer);
		return writer;
	}

	void Win32_FileSystem::deleteBinaryFileWriter(BinaryFileWriter* writer) {
		auto it = std::find(m_binaryWriters.begin(), m_binaryWriters.end(), writer);
		if (it != m_binaryWriters.end()) {
			m_binaryWriters.erase(it);
			//delete writer;
		}
	}

	TextFileReader* Win32_FileSystem::createTextFileReader(std::string directory) {
		TextFileReader* reader = new Win32_TextFileReader(directory);
		m_textReaders.push_back(reader);
		return reader;
	}

	void Win32_FileSystem::deleteTextFileReader(TextFileReader* reader) {
		auto it = std::find(m_textReaders.begin(), m_textReaders.end(), reader);
		if (it != m_textReaders.end()) {
			m_textReaders.erase(it);
			//delete reader;
		}
	}

	TextFileWriter* Win32_FileSystem::createTextFileWriter(std::string directory) {
		TextFileWriter* writer = new Win32_TextFileWriter(directory);
		m_textWriters.push_back(writer);
		return writer;
	}

	void Win32_FileSystem::deleteTextFileWriter(TextFileWriter* writer) {
		auto it = std::find(m_textWriters.begin(), m_textWriters.end(), writer);
		if (it != m_textWriters.end()) {
			m_textWriters.erase(it);
			//delete writer;
		}
	}

	void Win32_FileSystem::getAllFileNames(std::string directory, std::vector<std::string>& filenames, std::string ending){
		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			if (entry.is_regular_file()) {
				if (endsWith(entry.path().filename().string(),ending)) {
					filenames.push_back(entry.path().filename().string());
				}
			}
		}
	}
}