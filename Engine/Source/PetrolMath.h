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
	void benchmarkFunction2D(InputVector& in, sizeType vectorSize, T& function, const String& nameForLog) {
		// delay because in release mode log scope was called in the same ms, so graphs would be overlapping
		// and gives a moment to rest for cpu
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		LOG_SCOPE(nameForLog.c_str());

		for (sizeType i = 0; i < vectorSize; i++)
			function(in.at(i));
	}

	template<typename InputVector, typename TargetFunc, typename Func>
	double compareAccuracy(InputVector& vec, sizeType vectorSize, TargetFunc& targetFunction, Func& function) {
		double dif = 0.0;

		for (sizeType i = 0; i < vectorSize; i++)
			dif += std::abs(targetFunction(vec.at(i)) - function(vec.at(i))) / vectorSize;

		return dif;
	}


	template<typename Output, typename Input>
	inline Output TreatAs(Input& value) {
		return *reinterpret_cast<Output*>(&value);
	}

	inline float NegateFloat(float& f) {
        static_assert(sizeof(float) == sizeof(uint32), "casting types with different sizes.");
		return TreatAs<float>(TreatAs<uint32>(f) ^ 0x80000000);
	}


	float Log2(float x) {
		return float(TreatAs<uint>(x) - OneAsInt) * ScaleDown;
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
		const float threeHalf = 1.5F;

		x2 = x * 0.5F;
		y = x;
		i = *reinterpret_cast<int*>(&y);
		i = 0x5f3759df - (i >> 1);

		y = *reinterpret_cast<float*>(&i);
		y = y * (threeHalf - (x2 * y * y));
		return y;
	}

	// Better version of quake inverse root square
	float iSqrt(float x) {
		float xhalf = 0.5f * x;
		int   i     = *reinterpret_cast<int*>(&x);

		i = 0x5f375a86 - (i >> 1); // gives initial guess y0
		x = *reinterpret_cast<float*>(&i);

		x = x * (1.5f - xhalf * x * x); // Newton step

		return x;
	}

	void testMathFunctions(sizeType iterations = 100000, std::string&& outputPath = "Result.json") {
		std::vector<float> input;
		input.reserve(iterations);

		// Set directory for logger
        PetrolEngine::Debuging::Logger::setOutputFile(outputPath);

		for (uint32_t i = 0; i < iterations; i++)
			input.emplace_back((i / 100) + 1); // + 1 because Sqrt, iSqrt... does not support 0 and below

		{
			std::cout << "math sqrt      to cpp sqrt accuracy: " << compareAccuracy(input, iterations, sqrtl, Sqrt) << std::endl;
			std::cout << "math sqrt + NS to cpp sqrt accuracy: " << compareAccuracy(input, iterations, sqrtl, SqrtRep) << std::endl;

			LOG_SCOPE("sqrt");

			benchmarkFunction2D(input, iterations, sqrtf, "cpp sqrt");
			benchmarkFunction2D(input, iterations, SqrtRep, "'math' sqrt + newton step");
			benchmarkFunction2D(input, iterations, Sqrt   , "'math' sqrt");
		}
		{
			auto normal_iSqrt = [](float x) {return 1.0f / std::sqrtf(x); };

			std::cout << "math quake iSqrt to cpp iSqrt accuracy: " << compareAccuracy(input, iterations, normal_iSqrt, Quake_iSqrt) << std::endl;
			std::cout << "math       iSqrt to cpp iSqrt accuracy: " << compareAccuracy(input, iterations, normal_iSqrt, iSqrt) << std::endl;

			LOG_SCOPE("isqrt");

			benchmarkFunction2D(input, iterations, normal_iSqrt, "cpp   isqrt"   );
			benchmarkFunction2D(input, iterations, Quake_iSqrt , "quake isqrt"   );
			benchmarkFunction2D(input, iterations, iSqrt       , "quake isqrt v2");
		}
		{
			std::cout << "math log2 to cpp log2 accuracy: " << compareAccuracy(input, iterations, log2l, Log2) << std::endl;

			LOG_SCOPE("log2");

			benchmarkFunction2D(input, iterations, log2f, "cpp log2");
			benchmarkFunction2D(input, iterations, Log2, "'math' log2");
		}
		{
			std::cout << "math exp2 to cpp exp2 accuracy: " << compareAccuracy(input, iterations, exp2l, Exp2) << std::endl;

			LOG_SCOPE("exp2");

			benchmarkFunction2D(input, iterations, exp2f, "cpp exp2");
			benchmarkFunction2D(input, iterations, Exp2, "'math' exp2");
		}
	}
}