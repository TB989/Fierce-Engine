#pragma once

#include "src/PlatformLayer/include/LoggingSystem.h"
#include "src/PlatformLayer/include/FileSystem.h"

#include <vector>

namespace Fierce {

	class Win32_FileSystem :public FileSystem {
	public:
		Win32_FileSystem();
		~Win32_FileSystem();

		void initSystem(std::string m_assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		ConsoleWriter* createConsoleWriter() override;
		void deleteConsoleWriter(ConsoleWriter* writer) override;

		BinaryFileReader* createBinaryFileReader(std::string directory) override;
		void deleteBinaryFileReader(BinaryFileReader* reader) override;

		BinaryFileWriter* createBinaryFileWriter(std::string directory) override;
		void deleteBinaryFileWriter(BinaryFileWriter* writer) override;

		TextFileReader* createTextFileReader(std::string directory) override;
		void deleteTextFileReader(TextFileReader* reader) override;

		TextFileWriter* createTextFileWriter(std::string directory) override;
		void deleteTextFileWriter(TextFileWriter* writer) override;

		void getAllFileNames(std::string directory, std::vector<std::string>& filenames, std::string ending) override;

	private:
		LoggingSystem* m_loggingSystem=nullptr;
		Logger* m_logger = nullptr;

		ConsoleWriter* m_consoleWriter=nullptr;
		std::vector<BinaryFileReader*> m_binaryReaders;
		std::vector<BinaryFileWriter*> m_binaryWriters;
		std::vector<TextFileReader*> m_textReaders;
		std::vector<TextFileWriter*> m_textWriters;
	};

}//end namespace