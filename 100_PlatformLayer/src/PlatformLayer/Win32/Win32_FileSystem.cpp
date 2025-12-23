#include "Win32_FileSystem.h"

#include "src/PlatformLayer/Win32/Win32_LoggingSystem.h"

#include "Win32_FileReaderWriter.h"

#include <filesystem>

#include "src/utils/FierceStrings.h"

namespace Fierce {
	Win32_FileSystem::Win32_FileSystem(){
		
	}

	Win32_FileSystem::~Win32_FileSystem(){
		for (IBinaryFileReader* reader : m_binaryReaders) {
			delete reader;
		}
		for (ITextFileReader* reader : m_textReaders) {
			delete reader;
		}
		for (IBinaryFileWriter* writer : m_binaryWriters) {
			delete writer;
		}
		for (ITextFileWriter* writer : m_textWriters) {
			delete writer;
		}
	}

	void Win32_FileSystem::initSystem(std::string m_assetDirectory) {
		if (m_loggingSystem!=nullptr) {
			m_logger = m_loggingSystem->createLogger("FILE",true,"IO");
			m_logger->info("Init file system");
		}
	}

	void Win32_FileSystem::linkSystem(System* system){
		if (dynamic_cast<ILoggingSystem*>(system)) {
			m_loggingSystem = (ILoggingSystem*)system;
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

	std::string Win32_FileSystem::getName(){
		return "FileSystem";
	}

	IConsoleWriter* Win32_FileSystem::createConsoleWriter(){
		if (m_consoleWriter==nullptr) {
			m_consoleWriter = new Win32_ConsoleWriter();
		}
		return m_consoleWriter;
	}

	void Win32_FileSystem::deleteConsoleWriter(IConsoleWriter* writer){

	}

	IBinaryFileReader* Win32_FileSystem::createBinaryFileReader(std::string directory) {
		IBinaryFileReader* reader = new Win32_BinaryFileReader(directory);
		m_binaryReaders.push_back(reader);
		return reader;
	}

	void Win32_FileSystem::deleteBinaryFileReader(IBinaryFileReader* reader) {
		auto it = std::find(m_binaryReaders.begin(), m_binaryReaders.end(), reader);
		if (it != m_binaryReaders.end()) {
			m_binaryReaders.erase(it);
			delete reader;
		}
	}

	IBinaryFileWriter* Win32_FileSystem::createBinaryFileWriter(std::string directory) {
		IBinaryFileWriter* writer = new Win32_BinaryFileWriter(directory);
		m_binaryWriters.push_back(writer);
		return writer;
	}

	void Win32_FileSystem::deleteBinaryFileWriter(IBinaryFileWriter* writer) {
		auto it = std::find(m_binaryWriters.begin(), m_binaryWriters.end(), writer);
		if (it != m_binaryWriters.end()) {
			m_binaryWriters.erase(it);
			delete writer;
		}
	}

	ITextFileReader* Win32_FileSystem::createTextFileReader(std::string directory) {
		ITextFileReader* reader = new Win32_TextFileReader(directory);
		m_textReaders.push_back(reader);
		return reader;
	}

	void Win32_FileSystem::deleteTextFileReader(ITextFileReader* reader) {
		auto it = std::find(m_textReaders.begin(), m_textReaders.end(), reader);
		if (it != m_textReaders.end()) {
			m_textReaders.erase(it);
			delete reader;
		}
	}

	ITextFileWriter* Win32_FileSystem::createTextFileWriter(std::string directory) {
		ITextFileWriter* writer = new Win32_TextFileWriter(directory);
		m_textWriters.push_back(writer);
		return writer;
	}

	void Win32_FileSystem::deleteTextFileWriter(ITextFileWriter* writer) {
		auto it = std::find(m_textWriters.begin(), m_textWriters.end(), writer);
		if (it != m_textWriters.end()) {
			m_textWriters.erase(it);
			delete writer;
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