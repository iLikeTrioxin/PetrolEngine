#include <PCH.h>

#include "DebugTools.h"

#include <iostream>
#include <iomanip>
#include <sstream>

namespace PetrolEngine::Debugging {

	// Logger
	Logger Logger::logger;
	Logger::Logger() = default;
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
	void Logger::logFunction(const FunctionSpecification& spec) {
		if(!get().outputStream)
			setOutputFile("./Result.json");

		std::stringstream json;

		// Structure of json file for chromium profiling
		json << std::setprecision(3) << std::fixed;
		json << R"(,{)";
		json << R"("cat":"function",)";
		json << R"("dur":)" << spec.duration << ',';
		json << R"("name":")" << spec.name << "\",";
		json << R"("ph":"X",)";
		json << R"("pid":0,)";
		json << R"("tid":)" << spec.threadID << ",";
		json << R"("ts":)" << spec.startTimePoint;
		json << R"(})";

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