#pragma once

#include <Aliases.h>
#include <vector>
#include <chrono>

#if defined(__linux__)
#    define BM_CLOCK std::chrono::system_clock
#else
#    define BM_CLOCK std::chrono::steady_clock
#endif

namespace PetrolEngine{

    class Benchmarker {
    public:
        void frameDone();

        Benchmarker();

        MAYBE_UNUSED NO_DISCARD double    getOnePercentLow();
        MAYBE_UNUSED NO_DISCARD double getDotOnePercentLow();
        MAYBE_UNUSED NO_DISCARD double getAVG();
        MAYBE_UNUSED NO_DISCARD double getMax();
        MAYBE_UNUSED NO_DISCARD double getMin();

        void clear();

    private:
        Vector<uint32> deltaTimes;
        double pt = 0;
        std::chrono::time_point<BM_CLOCK> previousTimePoint;
        bool sorted = false;
    };
}