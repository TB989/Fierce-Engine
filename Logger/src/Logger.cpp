#include "Logger.h"

#include "time.h"
#include <filesystem>

namespace Fierce {

    HANDLE Logger::m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string Logger::m_logDirectory = "";
    std::unordered_map<std::string, FILE*> Logger::m_openFiles;

    Logger::Logger(std::string name) {
        m_name = name;
        m_stream = NULL;

        m_logToFile = false;
        m_logToConsole = true;

        m_c_useColors = true;
        m_c_printName = true;
        m_c_printLogLevel = false;
        m_c_printDate = false;
        m_c_printTime = true;

        m_f_printName = true;
        m_f_printLogLevel = true;
        m_f_printDate = false;
        m_f_printTime = true;
    }

    Logger::Logger(std::string name, bool logToConsole, std::string file) {
        m_name = name;
        m_stream = NULL;

        m_logToFile = true;
        m_logToConsole = logToConsole;

        m_c_useColors = true;
        m_c_printName = true;
        m_c_printLogLevel = false;
        m_c_printDate = false;
        m_c_printTime = true;

        m_f_printName = true;
        m_f_printLogLevel = true;
        m_f_printDate = false;
        m_f_printTime = true;

        std::string fullPath = createFullFilePath(file);
        fullPath = generateNotExistingFileNameAndOpen(fullPath);
    }

    void Logger::log(const char* logLevel, const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_printDate || m_c_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_c_printName)
                fprintf(stdout, "[%s]", m_name.c_str());
            if (m_c_printLogLevel)
                fprintf(stdout, "[%s]", logLevel);

            fprintf(stdout, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(stdout, format, args);
            va_end(args);
            fprintf(stdout, "\n");
        }

        if (m_logToFile) {
            if (m_f_printDate || m_f_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_f_printName)
                fprintf(m_stream, "[%s]", m_name.c_str());
            if (m_f_printLogLevel)
                fprintf(m_stream, "[%s]", logLevel);

            fprintf(m_stream, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(m_stream, format, args);
            va_end(args);
            fprintf(m_stream, "\n");
        }
    }

    void Logger::info(const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_useColors)
                SetConsoleTextAttribute(m_handle, 2);
            if (m_c_printDate || m_c_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_c_printName)
                fprintf(stdout, "[%s]", m_name.c_str());
            if (m_c_printLogLevel)
                fprintf(stdout, "[%s]", "INFO");

            fprintf(stdout, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(stdout, format, args);
            va_end(args);
            fprintf(stdout, "\n");
        }

        if (m_logToFile) {
            if (m_f_printDate || m_f_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_f_printName)
                fprintf(m_stream, "[%s]", m_name.c_str());
            if (m_f_printLogLevel)
                fprintf(m_stream, "[%s]", "INFO");

            fprintf(m_stream, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(m_stream, format, args);
            va_end(args);
            fprintf(m_stream, "\n");
        }
    }

    void Logger::warn(const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_useColors)
                SetConsoleTextAttribute(m_handle, 6);
            if (m_c_printDate || m_c_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_c_printName)
                fprintf(stdout, "[%s]", m_name.c_str());
            if (m_c_printLogLevel)
                fprintf(stdout, "[%s]", "WARN");

            fprintf(stdout, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(stdout, format, args);
            va_end(args);
            fprintf(stdout, "\n");
        }

        if (m_logToFile) {
            if (m_f_printDate || m_f_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_f_printName)
                fprintf(m_stream, "[%s]", m_name.c_str());
            if (m_f_printLogLevel)
                fprintf(m_stream, "[%s]", "WARN");

            fprintf(m_stream, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(m_stream, format, args);
            va_end(args);
            fprintf(m_stream, "\n");
        }
    }

    void Logger::error(const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_useColors)
                SetConsoleTextAttribute(m_handle, 4);
            if (m_c_printDate || m_c_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_c_printName)
                fprintf(stdout, "[%s]", m_name.c_str());
            if (m_c_printLogLevel)
                fprintf(stdout, "[%s]", "ERROR");

            fprintf(stdout, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(stdout, format, args);
            va_end(args);
            fprintf(stdout, "\n");
        }

        if (m_logToFile) {
            if (m_f_printDate || m_f_printTime) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
            }
            if (m_f_printName)
                fprintf(m_stream, "[%s]", m_name.c_str());
            if (m_f_printLogLevel)
                fprintf(m_stream, "[%s]", "ERROR");

            fprintf(m_stream, ": ");
            va_list args;
            va_start(args, format);
            vfprintf(m_stream, format, args);
            va_end(args);
            fprintf(m_stream, "\n");
        }
    }

    void Logger::init(std::string logDirectory) {
        m_logDirectory = logDirectory;
    }

    void Logger::cleanUp() {
        for (auto pair : m_openFiles) {
            fclose(pair.second);
        }
    }

    std::string Logger::createFullFilePath(std::string file) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        std::string fullPath = m_logDirectory;
        fullPath.append(std::to_string(1900 + ltm->tm_year))
            .append("_")
            .append(std::to_string(1 + ltm->tm_mon))
            .append("_")
            .append(std::to_string(ltm->tm_mday))
            .append("_")
            .append(file);

        return fullPath;
    }

    std::string Logger::generateNotExistingFileNameAndOpen(std::string fullPath) {
        std::string temporaryFileName;
        int counter = 1;

        while (true) {
            temporaryFileName = fullPath;
            temporaryFileName.append("_").append(std::to_string(counter)).append(".log");

            if (m_openFiles.find(temporaryFileName) != m_openFiles.end()) {
                m_stream = m_openFiles[temporaryFileName];
                return temporaryFileName;
            }

            if (std::filesystem::exists(temporaryFileName)) {
                counter++;
            }
            else {
                m_stream = fopen(temporaryFileName.c_str(), "w");
                m_openFiles[temporaryFileName] = m_stream;
                return temporaryFileName;
            }
        }
    }

}//end namespace