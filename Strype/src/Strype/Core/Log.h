#pragma once

#include "Strype/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Strype {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define STY_CORE_TRACE(...)    ::Strype::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define STY_CORE_INFO(...)     ::Strype::Log::GetCoreLogger()->info(__VA_ARGS__)
#define STY_CORE_WARN(...)     ::Strype::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define STY_CORE_ERROR(...)    ::Strype::Log::GetCoreLogger()->error(__VA_ARGS__)
#define STY_CORE_CRITICAL(...) ::Strype::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define STY_TRACE(...)		   ::Strype::Log::GetClientLogger()->trace(__VA_ARGS__)
#define STY_INFO(...)	       ::Strype::Log::GetClientLogger()->info(__VA_ARGS__)
#define STY_WARN(...)	       ::Strype::Log::GetClientLogger()->warn(__VA_ARGS__)
#define STY_ERROR(...)	       ::Strype::Log::GetClientLogger()->error(__VA_ARGS__)
#define STY_CRITICAL(...)	   ::Strype::Log::GetClientLogger()->critical(__VA_ARGS__)