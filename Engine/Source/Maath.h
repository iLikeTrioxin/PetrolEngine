#include <Aliases.h>

#include <chrono>
#include <thread>
#include <iostream>
#include "DebugTools.h"

// TODO repair unsafe conversions and add logging

namespace PetrolEngine::Math {

	const uint64_t OneAsInt = 0x3F800000;
	const float    ScaleUp = 0x00800000;
	const float    ScaleDown = 1.0f / ScaleUp;

	template<typename InputVector, typename T>
	void benchmarkFunction2D(InputVector& in, size_t vectorSize, T& function, String nameForLog) {
		// delay because in release mode log scope was called in the same ms, so graphs would be overlapping
		// and gives a moment to rest for cpu
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		LOG_SCOPE(nameForLog.c_str());

		for (size_t i = 0; i < vectorSize; i++)
			function(in.at(i));
	}

	template<typename inputVector, typename targetFunc, typename func>
	double compareAccuracy(inputVector& vec, size_t vectorSize, targetFunc& targetFunction, func& function) {
		double dif = 0.0;

		for (size_t i = 0; i < vectorSize; i++)
			dif += std::abs(targetFunction(vec.at(i)) - function(vec.at(i))) / vectorSize;

		return dif;
	}


	template<typename Output, typename Input>
	inline Output TreatAs(Input value) {
		return *reinterpret_cast<Output*>(&value);
	}

	inline float NegateFloat(float& f) {
        //DEBUG_LOG((sizeof(float) != sizeof(uint32)));
		return TreatAs<uint32, float>(*reinterpret_cast<uint32*>(&f) ^ 0x80000000);
	}


	float Log2(float x) {
		return float(TreatAs<unsigned int>(x) - OneAsInt) * ScaleDown;
	}

	float Exp2(float x) {
		return TreatAs<float>(int(x * ScaleUp) + OneAsInt);
	}

	float Pow(float x, float p) {
		return TreatAs<float>(int(p * (TreatAs<float, unsigned int>(x) - OneAsInt)) + OneAsInt);
	}

	float Sqrt(float x) {
		return TreatAs<float>((TreatAs<unsigned int>(x) >> 1) + (OneAsInt >> 1));
	}

	float SqrtRep(float x) {
		float y = Sqrt(x);
		return (y * y + x) / (2 * y);
	}

	float Quake_iSqrt(float x) {
		int i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = x * 0.5F;
		y = x;
		i = *reinterpret_cast<int*>(&y);
		i = 0x5f3759df - (i >> 1);

		y = *reinterpret_cast<float*>(&i);
		y = y * (threehalfs - (x2 * y * y));
		return y;
	}

	// Better version of quake inverse root squere
	float iSqrt(float x) {
		float xhalf = 0.5f * x;
		int   i     = *reinterpret_cast<int*>(&x);

		i = 0x5f375a86 - (i >> 1); // gives initial guess y0
		x = *reinterpret_cast<float*>(&i);

		x = x * (1.5f - xhalf * x * x); // Newton step

		return x;
	}

	void testMathFunctions(size_t iters = 100000, std::string&& outputPath = "Result.json") {
		std::vector<float> input;
		input.reserve(iters);

		// Set directory for logger
        PetrolEngine::Debuging::Logger::setOutputFile(outputPath);

		for (uint32_t i = 0; i < iters; i++)
			input.emplace_back((i / 100) + 1); // + 1 becouse Sqrt, iSqrt... does not support 0 and below

		{
			std::cout << "math sqrt      to cpp sqrt accuracy: " << compareAccuracy(input, iters, sqrtl, Sqrt) << std::endl;
			std::cout << "math sqrt + NS to cpp sqrt accuracy: " << compareAccuracy(input, iters, sqrtl, SqrtRep) << std::endl;

			LOG_SCOPE("sqrt");

			benchmarkFunction2D(input, iters, sqrtf, "cpp sqrt");
			benchmarkFunction2D(input, iters, SqrtRep, "'math' sqrt + newton step");
			benchmarkFunction2D(input, iters, Sqrt   , "'math' sqrt");
		}
		{
			auto normal_iSqrt = [](float x) {return 1.0f / std::sqrtf(x); };

			std::cout << "math quake iSqrt to cpp iSqrt accuracy: " << compareAccuracy(input, iters, normal_iSqrt, Quake_iSqrt) << std::endl;
			std::cout << "math       iSqrt to cpp iSqrt accuracy: " << compareAccuracy(input, iters, normal_iSqrt, iSqrt) << std::endl;

			LOG_SCOPE("isqrt");

			benchmarkFunction2D(input, iters, normal_iSqrt, "cpp isqrt");
			benchmarkFunction2D(input, iters, Quake_iSqrt, "quake isqrt");
			benchmarkFunction2D(input, iters, iSqrt, "'math' isqrt");
		}
		{
			std::cout << "math log2 to cpp log2 accuracy: " << compareAccuracy(input, iters, log2l, Log2) << std::endl;

			LOG_SCOPE("log2");

			benchmarkFunction2D(input, iters, log2f, "cpp log2");
			benchmarkFunction2D(input, iters, Log2, "'math' log2");
		}
		{
			std::cout << "math exp2 to cpp exp2 accuracy: " << compareAccuracy(input, iters, exp2l, Exp2) << std::endl;

			LOG_SCOPE("exp2");

			benchmarkFunction2D(input, iters, exp2f, "cpp exp2");
			benchmarkFunction2D(input, iters, Exp2, "'math' exp2");
		}
	}
}