#pragma once

#include <chrono>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

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

	// measures time between creation and destruction.
	class ScopeTimer {
	public:
		explicit ScopeTimer(const char* name);
		~ScopeTimer();
	private:
		const char* name;
		std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
	};
};