#pragma once

#include "src/systems/ILoggingSystem.h"
#include "src/systems/IFileSystem.h"

#include <vector>

namespace Fierce {

	class Win32_FileSystem :public IFileSystem{
	public:
		Win32_FileSystem();
		~Win32_FileSystem();

		void initSystem(std::string m_assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		std::string getName() override;

		IConsoleWriter* createConsoleWriter() override;
		void deleteConsoleWriter(IConsoleWriter* writer) override;

		IBinaryFileReader* createBinaryFileReader(std::string directory) override;
		void deleteBinaryFileReader(IBinaryFileReader* reader) override;

		IBinaryFileWriter* createBinaryFileWriter(std::string directory) override;
		void deleteBinaryFileWriter(IBinaryFileWriter* writer) override;

		ITextFileReader* createTextFileReader(std::string directory) override;
		void deleteTextFileReader(ITextFileReader* reader) override;

		ITextFileWriter* createTextFileWriter(std::string directory) override;
		void deleteTextFileWriter(ITextFileWriter* writer) override;

		void getAllFileNames(std::string directory, std::vector<std::string>& filenames, std::string ending) override;

	private:
		ILoggingSystem* m_loggingSystem=nullptr;
		ILogger* m_logger = nullptr;

		IConsoleWriter* m_consoleWriter=nullptr;
		std::vector<IBinaryFileReader*> m_binaryReaders;
		std::vector<IBinaryFileWriter*> m_binaryWriters;
		std::vector<ITextFileReader*> m_textReaders;
		std::vector<ITextFileWriter*> m_textWriters;
	};

}//end namespace