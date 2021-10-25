#pragma once

#include <aliases.h>
#include <vector>

#if defined(__linux__)
#define clock std::chrono::system_clock
#else
#define clock std::chrono::steady_clock
#endif

namespace PetrolEngine{

    class Benchmarker {
    public:
        double(*timeFunction)() = nullptr;
        void frameDone();

        explicit Benchmarker(void* _timeFunction) : timeFunction(reinterpret_cast<double(*)()>(_timeFunction)), previousTimePoint(timeFunction()) { deltaTimes.reserve(1000); }

        double    getOnePercentLow();
        double getDotOnePercentLow();
        double getAVG();
        double getMax();
        double getMin();

        void clear();

    private:
        std::vector<double> deltaTimes;
        double previousTimePoint = 0.0;
        bool   sorted = false;
    };
}