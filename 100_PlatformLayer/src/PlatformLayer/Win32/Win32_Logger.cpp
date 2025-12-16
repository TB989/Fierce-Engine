#include "Win32_Logger.h"

namespace Fierce {

    Win32_Logger::Win32_Logger(std::string name, ITextFileWriter* fileWriter, IConsoleWriter* consoleWriter){
        m_name = name;
        m_fileWriter = fileWriter;
        m_consoleWriter = consoleWriter;
        snprintf(m_nameBuffer, sizeof(m_nameBuffer), "[%s]", name.c_str());
    }

    void Win32_Logger::log(const char* logLevel, const char* format, ...) {
        char logLevelBuffer[15];
        snprintf(logLevelBuffer, sizeof(logLevelBuffer), "[%s]", logLevel);

        if (m_fileWriter!=nullptr) {
            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_fileWriter->print("%s%s%s%s: %s\n",
                m_f_printDate?m_dateBuffer : "",
                m_f_printTime ? m_timeBuffer : "",
                m_f_printName?m_nameBuffer : "",
                m_f_printLogLevel?logLevelBuffer:"",
                m_messageBuffer);
        }

        if (m_consoleWriter != nullptr) {
            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_consoleWriter->print("%s%s%s%s: %s\n",
                m_c_printDate ? m_dateBuffer : "",
                m_c_printTime ? m_timeBuffer : "",
                m_c_printName ? m_nameBuffer : "",
                m_c_printLogLevel ? logLevelBuffer : "",
                m_messageBuffer);
        }
    }

    void Win32_Logger::info(const char* format, ...) {
        if (m_fileWriter != nullptr) {
            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_fileWriter->print("%s%s%s%s: %s\n",
                m_f_printDate ? m_dateBuffer : "",
                m_f_printTime ? m_timeBuffer : "",
                m_f_printName ? m_nameBuffer : "",
                m_f_printLogLevel ? m_logLevelInfo : "",
                m_messageBuffer);
        }

        if (m_consoleWriter != nullptr) {
            if (m_c_useColors)
                m_consoleWriter->setColor(2);

            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_consoleWriter->print("%s%s%s%s: %s\n",
                m_c_printDate ? m_dateBuffer : "",
                m_c_printTime ? m_timeBuffer : "",
                m_c_printName ? m_nameBuffer : "",
                m_c_printLogLevel ? m_logLevelInfo : "",
                m_messageBuffer);
        }
    }

    void Win32_Logger::warn(const char* format, ...) {
        if (m_fileWriter != nullptr) {
            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_fileWriter->print("%s%s%s%s: %s\n",
                m_f_printDate ? m_dateBuffer : "",
                m_f_printTime ? m_timeBuffer : "",
                m_f_printName ? m_nameBuffer : "",
                m_f_printLogLevel ? m_logLevelWarn : "",
                m_messageBuffer);
        }

        if (m_consoleWriter != nullptr) {
            if (m_c_useColors)
                m_consoleWriter->setColor(6);

            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_consoleWriter->print("%s%s%s%s: %s\n",
                m_c_printDate ? m_dateBuffer : "",
                m_c_printTime ? m_timeBuffer : "",
                m_c_printName ? m_nameBuffer : "",
                m_c_printLogLevel ? m_logLevelWarn : "",
                m_messageBuffer);
        }
    }

    void Win32_Logger::error(const char* format, ...) {
        if (m_fileWriter != nullptr) {
            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_fileWriter->print("%s%s%s%s: %s\n",
                m_f_printDate ? m_dateBuffer : "",
                m_f_printTime ? m_timeBuffer : "",
                m_f_printName ? m_nameBuffer : "",
                m_f_printLogLevel ? m_logLevelError : "",
                m_messageBuffer);
        }

        if (m_consoleWriter != nullptr) {
            if (m_c_useColors)
                m_consoleWriter->setColor(4);

            va_list args;
            va_start(args, format);
            vsnprintf(m_messageBuffer, sizeof(m_messageBuffer), format, args);
            va_end(args);

            m_consoleWriter->print("%s%s%s%s: %s\n",
                m_c_printDate ? m_dateBuffer : "",
                m_c_printTime ? m_timeBuffer : "",
                m_c_printName ? m_nameBuffer : "",
                m_c_printLogLevel ? m_logLevelError : "",
                m_messageBuffer);
        }
    }

    void Win32_Logger::update(int year, int month, int day, int hours, int minutes, int seconds){
        snprintf(m_dateBuffer, sizeof(m_dateBuffer), "[%i\.%i\.%i]", day,month,year);
        snprintf(m_timeBuffer, sizeof(m_timeBuffer), "[%i:%i:%i]", hours,minutes,seconds);
    }

    void Win32_Logger::setConsoleUseColors(bool useColors){
        m_c_useColors = useColors;
    }

    void Win32_Logger::setConsolePrintName(bool printName){
        m_c_printName = printName;
    }

    void Win32_Logger::setConsolePrintLogLevel(bool printLogLevel){
        m_c_printLogLevel = printLogLevel;
    }

    void Win32_Logger::setConsolePrintDate(bool printDate){
        m_c_printDate = printDate;
    }

    void Win32_Logger::setConsolePrintTime(bool printTime){
        m_c_printTime = printTime;
    }

    void Win32_Logger::setFilePrintName(bool printName){
        m_f_printName = printName;
    }

    void Win32_Logger::setFilePrintLogLevel(bool printLogLevel){
        m_f_printLogLevel = printLogLevel;
    }

    void Win32_Logger::setFilePrintDate(bool printDate){
        m_f_printDate = printDate;
    }

    void Win32_Logger::setFilePrintTime(bool printTime){
        m_f_printTime = printTime;
    }

}//end namespace