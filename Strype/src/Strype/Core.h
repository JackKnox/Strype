#pragma once

#include <memory>

#define STY_ASSERT(x, ...) { if(!(x)) { STY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define STY_CORE_ASSERT(x, ...) { if(!(x)) { STY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define BIT(x) (1 << x)

#define STY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Strype {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}