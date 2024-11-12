#include "stypch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Strype {

	std::shared_ptr<spdlog::logger> Log::sCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		sCoreLogger = spdlog::stdout_color_mt("STRYPE");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("APP");
		sClientLogger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Log::GetCoreLogger() 
	{ 
		return sCoreLogger;
	}

	std::shared_ptr<spdlog::logger>& Log::GetClientLogger() 
	{ 
		return sClientLogger;
	}
}