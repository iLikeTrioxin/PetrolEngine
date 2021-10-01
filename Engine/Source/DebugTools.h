#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

namespace PetrolEngine::Debuging {

	using TimeUnit = std::chrono::microseconds;

	//
	// self explanatory I think
	//
	struct FunctionSpecification {
		std::thread::id threadID;
		std::string     name;
		long long       startTimePoint;
		long long       duration;
	};

	//
	// Logging system
	//
	class Logger {
	public:
		static void logFunction(FunctionSpecification spec);
		static void setOutputFile(const std::string& filePath);

	private:
		static Logger logger;
		std::ofstream outputStream;
		std::  mutex  mutex;

		Logger();
		~Logger();
		static Logger& get();
		void log(std::string& input);
		void log(std::string&& input);
	};

	//
	//@brief measures time between creation and destruction.
	//
	class ScopeTimer {
	public:
		ScopeTimer(const char* name);
		~ScopeTimer();
	private:
		const char* name;
		std::chrono::time_point<std::chrono::system_clock> startTimePoint;
	};
};

#if defined(__GNUC__)
    #define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
	#define FUNCTION_NAME __FUNCSIG__
#elif defined(__INTEL_COMPILER)
	#define FUNCTION_NAME __FUNCTION__
#elif defined(__STDC_VERSION__)
	#define FUNCTION_NAME __func__
#elif defined(__cplusplus)
	#define FUNCTION_NAME __func__
#else
	#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
#endif

#define ENGINE_DEBUG
#ifdef ENGINE_DEBUG

#define LOG_SCOPE_LINE(name, line) PetrolEngine::Debuging::ScopeTimer timer##line(name)
#define LOG_FUNCTION()  LOG_SCOPE_LINE(FUNCTION_NAME, __LINE__)
#define DEBUG_OPENGL() { debug_log("Context:"<<FUNCTION_NAME<<"#"<<__LINE__); Renderer::getErrors(); }
#define LOG_SCOPE(name) LOG_SCOPE_LINE(    name    , __LINE__)

#else

// If not debugging then replace those with nothing
#define LOG_FUNCTION()
#define LOG_SCOPE(x)

#endif