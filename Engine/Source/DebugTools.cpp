#include <PCH.h>

#include "DebugTools.h"

#include <iostream>
#include <iomanip>

namespace PetrolEngine::Debugging {

	// Logger
	Logger Logger::logger;
	Logger::Logger() {
	}
	Logger::~Logger() {
		std::lock_guard lock(mutex);
		log(std::string("]}")); // Footer
	}
	Logger& Logger::get() { return logger; }
	void Logger::log(std::string& input) {
		if (!outputStream)
			return;
		
		outputStream << input;
		outputStream.flush();
	}
	void Logger::log(std::string&& input) {
		if (!outputStream)
			return;

		outputStream << input;
		outputStream.flush();
	}
	void Logger::logFunction(FunctionSpecification spec) {
		if(!get().outputStream)
			get().setOutputFile("./Result.json");

		std::stringstream json;

		// Structure of json file for chromium profiling
		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << spec.duration << ',';
		json << "\"name\":\"" << spec.name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << spec.threadID << ",";
		json << "\"ts\":" << spec.startTimePoint;
		json << "}";

		std::lock_guard lock(get().mutex);
		get().log(json.str());
	}
	void Logger::setOutputFile(const std::string& filePath) {
		std::lock_guard lock(get().mutex);

		// write footer if already opened
		if (get().outputStream)
			get().log(std::string("]}"));

		get().outputStream.open(filePath);

		// Write header for the file
		get().log(R"({"otherData":{},"traceEvents":[{})");
	}

	// ScopeTimer
	ScopeTimer::ScopeTimer(const char* name): name(name), startTimePoint(std::chrono::high_resolution_clock::now()) {}
	ScopeTimer::~ScopeTimer() {
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<TimeUnit>(startTimePoint).time_since_epoch().count();
		long long end   = std::chrono::time_point_cast<TimeUnit>(  endTimePoint).time_since_epoch().count();

		Logger::logFunction({ std::this_thread::get_id(), std::string(name), start, end - start });
	}
}