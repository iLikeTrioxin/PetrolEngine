#include "Benchmarker.h"
#include <GLFW/glfw3.h>
#include <algorithm>

// This benchmarker is fucked up
// TODO: Complete rework

namespace PetrolEngine{

    struct sortDouble {
        bool operator()(double a, double b) const { return a > b; }
    };

    Benchmarker::Benchmarker() {
        deltaTimes.reserve(4096);
        previousTimePoint = std::chrono::high_resolution_clock::now();
    }

    void Benchmarker::frameDone() {
        //auto currentTimePoint = std::chrono::high_resolution_clock::now();

        //uint64 start = std::chrono::time_point_cast<Debugging::TimeUnit>(previousTimePoint).time_since_epoch().count();
        //uint64 end   = std::chrono::time_point_cast<Debugging::TimeUnit>( currentTimePoint).time_since_epoch().count();
        uint32 a = glfwGetTime() * 100000000;
        deltaTimes.emplace_back( a - pt );

        pt = a;

        if(deltaTimes.size()>>16) deltaTimes.erase(deltaTimes.begin() + (1<<12), deltaTimes.begin() + (1 << 15));

        sorted = false;
    }

    double Benchmarker::getDotOnePercentLow() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        // divide size by 1024 as it is faster than dividing by 1000 (*0.001)
        uint32 dotOnePercentSize = deltaTimes.size() >> 10;

        uint64 a1 = 0;
        uint64 a2 = 0;

        // this loop can skip 1 frame (that small mistake is acceptable)
        for(uint32 i=0; i < dotOnePercentSize; i+=2){
            a1 += deltaTimes[i + 0];
            a2 += deltaTimes[i + 1];
        }

        return 100000000.0 * dotOnePercentSize / (double) (a1 + a2);
    }

    double Benchmarker::getOnePercentLow() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        // divide size by 128 as it is faster than dividing by 100 (*0.01)
        uint32 onePercentSize = deltaTimes.size() >> 5;

        uint64 a1 = 0;
        uint64 a2 = 0;
        uint64 a3 = 0;
        uint64 a4 = 0;

        // this loop can skip up to 3 frames (that small mistake is acceptable)
        for(uint32 i=0; i < onePercentSize; i+=4){
            a1 += deltaTimes[i + 0];
            a2 += deltaTimes[i + 1];
            a3 += deltaTimes[i + 2];
            a4 += deltaTimes[i + 3];
        }

        return 100000000.0 * onePercentSize / (double) ( (a1 + a4) + (a2 + a3) );
    }

    double Benchmarker::getAVG() {
        // that many counters are required to prevent overflow
        uint64 c1 = 0;
        uint64 c2 = 0;
        uint64 c3 = 0;
        uint64 c4 = 0;
        uint64 c5 = 0;
        uint64 c6 = 0;
        uint64 c7 = 0;
        uint64 c8 = 0;

        // this loop can skip up to 7 frames (that small mistake is acceptable)
        for(uint32 i=0; i < deltaTimes.size(); i+=8){
            c1 += deltaTimes[i + 0];
            c2 += deltaTimes[i + 1];
            c3 += deltaTimes[i + 2];
            c4 += deltaTimes[i + 3];
            c5 += deltaTimes[i + 4];
            c6 += deltaTimes[i + 5];
            c7 += deltaTimes[i + 6];
            c8 += deltaTimes[i + 7];
        }

        double ratio = 1.0 / (double) deltaTimes.size();

        double sum = 0.0;

        sum += (double) c1 * ratio;
        sum += (double) c2 * ratio;
        sum += (double) c3 * ratio;
        sum += (double) c4 * ratio;
        sum += (double) c5 * ratio;
        sum += (double) c6 * ratio;
        sum += (double) c7 * ratio;
        sum += (double) c8 * ratio;

        return 100000000.0 / sum;
    }

    double Benchmarker::getMax() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        return 100000000.0 / deltaTimes.back();
    }

    double Benchmarker::getMin() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        return 100000000.0 / deltaTimes.front();
    }

    void Benchmarker::clear() {
        deltaTimes.clear();
    }

}