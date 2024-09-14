#include "Logger.h"

#include "time.h"

namespace Fierce {

    Logger::Logger(std::string name, HANDLE handle, bool logToConsole, bool logToFile, FILE* stream) {
        m_name = name;
        m_handle = handle;
        m_stream = stream;

        m_logToConsole = logToConsole;
        m_logToFile = logToFile;

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

}//end namespace