#pragma once

#ifdef STY_DEBUG
#	if defined(STY_WINDOWS)
#		define STY_DEBUGBREAK() __debugbreak()
#	elif defined(STY_LINUX)
#		include <signal.h>
#		define STY_DEBUGBREAK() raise(SIGTRAP)
#	else
#		error "Platform doesn't support debugbreak yet!"
#	endif
#else
#	define STY_DEBUGBREAK()
#endif

#define STY_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define BIT(x) (1 << x) 

namespace Strype {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#define STY_ENABLE_VERIFY

#ifdef STY_ENABLE_VERIFY
#	define STY_CORE_VERIFY(condition, ...) { if(!(condition)) { STY_CORE_ERROR(__VA_ARGS__); } }
#	define STY_VERIFY(condition, ...) { if(!(condition)) { STY_ERROR(__VA_ARGS__); } }
#else
#	define STY_CORE_VERIFY(condition, ...)
#	define STY_VERIFY(condition, ...)
#endif

//
// Build Configuration
//
#if defined(STY_DEBUG)
#	define STY_BUILD_CONFIG_NAME "Debug"
#elif defined(STY_RELEASE)
#	define STY_BUILD_CONFIG_NAME "Release"
#elif defined(STY_DIST)
#	define STY_BUILD_CONFIG_NAME "Dist"
#else
#	error Undefined configuration?
#endif

//
// Build Platform
//
#if defined(STY_WINDOWS)
#	define STY_BUILD_PLATFORM_NAME "Windows x64"
#elif defined(STY_LINUX)
#	define STY_BUILD_PLATFORM_NAME "Linux"
#else
#	error Undefined Platform?
#endif

#define STY_VERSION_LONG "Strype " STY_VERSION " (" STY_BUILD_PLATFORM_NAME " " STY_BUILD_CONFIG_NAME ")"