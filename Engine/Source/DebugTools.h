#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

#if defined(__linux__)
#    define DEBUG_TOOLS_CLOCK std::chrono::system_clock
#else
#    define DEBUG_TOOLS_CLOCK std::chrono::steady_clock
#endif

namespace PetrolEngine::Debugging {

	using TimeUnit = std::chrono::microseconds;

	// self-explanatory I think
	struct FunctionSpecification {
		std::thread::id threadID;
		std::string     name;
		long long       startTimePoint;
		long long       duration;
	};

	// Logging system
	class Logger {
	public:
		static void logFunction(const FunctionSpecification& spec);
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

	// measures time between creation and destruction.
	class ScopeTimer {
	public:
		explicit ScopeTimer(const char* name);
		~ScopeTimer();
	private:
		const char* name;

		std::chrono::time_point<DEBUG_TOOLS_CLOCK> startTimePoint;
	};
};

#define LOG_SCOPE_LINE2(name, line) PetrolEngine::Debugging::ScopeTimer timer##line(name)
#define LOG_SCOPE_LINE(name, line) LOG_SCOPE_LINE2(name, line)
#define LOG_SCOPE(name) LOG_SCOPE_LINE(name, __LINE__)
#define LOG_FUNCTION() LOG_SCOPE(CURRENT_FUNCTION)