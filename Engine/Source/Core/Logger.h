#pragma once

#include <Aliases.h>
#include <utility>
#include <string>

#define LOG(message, level) PetrolEngine::programLogger.log( String(constExprFilename(__FILE__)) + ":" + toString(__LINE__), message, level )

namespace PetrolEngine{
    class LogRecord{
    public:
        String source ; // From where does this log come from
        String message; // What does it contain

        // Suggested values (you can insert other numbers below or above those)
        // 1 - info
        // 2 - warning
        // 3 - error
        int type;

        LogRecord(String source, String message, int type): source(std::move(source)), message(std::move(message)), type(type) {}
    };

    class Logger{
    public:
        void log(LogRecord record);

        void log(String source, String message, int type);

    private:
        Vector<LogRecord> records;
    };

    extern Logger programLogger;
}

