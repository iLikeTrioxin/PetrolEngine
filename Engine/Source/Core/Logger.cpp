#include <PCH.h>

#include "Logger.h"

namespace PetrolEngine{
    Logger programLogger;

    void Logger::log(String source, String message, int type) {
        records.emplace_back( std::move( source),
                              std::move(message),
                              type                );
        //if(type != 3) return;

        std::cout<<records.back().source<<" - "<<records.back().message<<"\n";
    }

    void Logger::log(LogRecord record) {
        records.emplace_back(std::move(record));
    }
}