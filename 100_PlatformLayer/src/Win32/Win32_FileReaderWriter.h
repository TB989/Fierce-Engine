#pragma once

#include <Windows.h>

#include "src/include/FileSystem.h"

namespace Fierce {
    class Win32_FileIO : public FileIO {
    public:
        Win32_FileIO(std::string directory);

    protected:
        bool openFile(std::string filename,std::string options) override;
        void closeFile() override;

    protected:
        FILE* m_file = nullptr;
    };

    class Win32_ConsoleWriter:public ConsoleWriter{
    public:
        Win32_ConsoleWriter();
        virtual ~Win32_ConsoleWriter();

        void print(const char* format, ...) override;
        void setColor(int color) override;

    private:
        HANDLE m_handle=NULL;
    };

    class Win32_BinaryFileReader : public Win32_FileIO,public BinaryFileReader {
    public:
        Win32_BinaryFileReader(std::string directory);
        virtual ~Win32_BinaryFileReader();

        bool openFile(std::string filename) override;
        bool readBinary(long* size, char** buffer) override;
        void closeFile() override;
    };

    class Win32_BinaryFileWriter : public Win32_FileIO, public BinaryFileWriter {
    public:
        Win32_BinaryFileWriter(std::string directory);
        virtual ~Win32_BinaryFileWriter();

        bool openFile(std::string filename) override;
        void closeFile() override;
    };

    class Win32_TextFileReader : public Win32_FileIO, public TextFileReader {
    public:
        Win32_TextFileReader(std::string directory);
        virtual ~Win32_TextFileReader();

        bool openFile(std::string filename) override;
        bool readNextLine(std::string& line) override;
        void closeFile() override;
    };

    class Win32_TextFileWriter : public Win32_FileIO, public TextFileWriter {
    public:
        Win32_TextFileWriter(std::string directory);
        virtual ~Win32_TextFileWriter();

        bool openFile(std::string filename) override;
        void print(const char* format, ...) override;
        void closeFile() override;
    };
}