#include "Win32_Logger.h"

namespace Fierce {

    Win32_Logger::Win32_Logger(std::string name, HANDLE handle, bool logToConsole, bool logToFile, FILE* stream) :Logger(name, logToConsole,logToFile){
        m_handle = handle;
        m_stream = stream;
    }

    void Win32_Logger::log(const char* logLevel, const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_printDate || m_c_printTime) {
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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

    void Win32_Logger::info(const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_useColors)
                SetConsoleTextAttribute(m_handle, 2);
            if (m_c_printDate || m_c_printTime) {
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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

    void Win32_Logger::warn(const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_useColors)
                SetConsoleTextAttribute(m_handle, 6);
            if (m_c_printDate || m_c_printTime) {
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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

    void Win32_Logger::error(const char* format, ...) {
        if (m_logToConsole) {
            if (m_c_useColors)
                SetConsoleTextAttribute(m_handle, 4);
            if (m_c_printDate || m_c_printTime) {
                if (m_c_printDate)
                    fprintf(stdout, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_c_printTime)
                    fprintf(stdout, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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
                if (m_f_printDate)
                    fprintf(m_stream, "[%i\.%i\.%i]", m_day, m_month, m_year);
                if (m_f_printTime)
                    fprintf(m_stream, "[%i:%i:%i]", m_hours, m_minutes, m_seconds);
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

    void Win32_Logger::update(int year, int month, int day, int hours, int minutes, int seconds){
        m_year = year;
        m_month = month;
        m_day = day;

        m_hours = hours;
        m_minutes = minutes;
        m_seconds = seconds;
    }

}//end namespace