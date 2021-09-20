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


#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
    #define HZ_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
    #define HZ_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
	#define HZ_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define HZ_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define HZ_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define HZ_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define HZ_FUNC_SIG __func__
#else
	#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
#endif

#define ENGINE_DEBUG
#ifdef ENGINE_DEBUG

#define LOG_SCOPE_LINE(name, line) PetrolEngine::Debuging::ScopeTimer timer##line(name)
#define LOG_FUNCTION()  LOG_SCOPE_LINE(HZ_FUNC_SIG, __LINE__)
#define DEBUG_OPENGL() { debug_log("Context:"<<__FUNCTION__<<"#"<<__LINE__); Renderer::getErrors(); }
#define LOG_SCOPE(name) LOG_SCOPE_LINE(    name    , __LINE__)

#else

// If not debugging then replace those with nothing
#define LOG_FUNCTION()
#define LOG_SCOPE(x)

#endif