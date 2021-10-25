#include "Benchmarker.h"

#include <algorithm>

namespace PetrolEngine{

    struct sortDouble {
        bool operator()(double a, double b) const { return a > b; }
    };

    void Benchmarker::frameDone() {
        double currentTimePoint = timeFunction();
        
        deltaTimes.emplace_back(currentTimePoint - previousTimePoint);

        previousTimePoint = currentTimePoint;
        sorted = false;
    }

    double Benchmarker::getDotOnePercentLow() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        int dotOnePercentSize = deltaTimes.size() * 0.001;

        double a1 = 0.0;
        double a2 = 0.0;
        double a3 = 0.0;
        double a4 = 0.0;

        // this loop can skip up to 3 frames (that small mistake is acceptable)
        for(uint64 i=0; i < dotOnePercentSize; i+=4){
            a1 += deltaTimes[i + 0];
            a2 += deltaTimes[i + 1];
            a3 += deltaTimes[i + 2];
            a4 += deltaTimes[i + 3];
        }

        return ( (a1 + a2) + (a3 + a4) ) / dotOnePercentSize;
    }

    double Benchmarker::getOnePercentLow() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        int onePercentSize = deltaTimes.size() * 0.01;

        double a1 = 0.0;
        double a2 = 0.0;
        double a3 = 0.0;
        double a4 = 0.0;

        // this loop can skip up to 3 frames (that small mistake is acceptable)
        for(uint64 i=0; i < onePercentSize; i+=4){
            a1 += deltaTimes[i + 0];
            a2 += deltaTimes[i + 1];
            a3 += deltaTimes[i + 2];
            a4 += deltaTimes[i + 3];
        }

        return ( (a1 + a2) + (a3 + a4) ) / onePercentSize;
    }

    double Benchmarker::getAVG() {
        double a1 = 0.0;
        double a2 = 0.0;
        double a3 = 0.0;
        double a4 = 0.0;
        
        int size = deltaTimes.size() - (deltaTimes.size() % 4);

        // this loop can skip up to 3 frames (that small mistake is acceptable)
        for(uint64 i=0; i < size; i+=4){
            a1 += deltaTimes[i + 0];
            a2 += deltaTimes[i + 1];
            a3 += deltaTimes[i + 2];
            a4 += deltaTimes[i + 3];
        }

        return ( (a1 + a2) + (a3 + a4) ) / size;
    }

    double Benchmarker::getMax() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        return deltaTimes.back();
    }

    double Benchmarker::getMin() {
        if(!sorted) { std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble()); sorted = true; }

        return deltaTimes.front();
    }

    void Benchmarker::clear() {
        deltaTimes.clear();
    }

}