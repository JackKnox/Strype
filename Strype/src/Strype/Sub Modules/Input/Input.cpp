#include "stypch.h"
#include "Input.h"

#ifdef STY_PLATFORM_WINDOWS
#	include "API/GLFW/GlfwInput.h"
#endif

namespace Strype {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef STY_PLATFORM_WINDOWS
		return CreateScope<GlfwInput>();
	#else
		STY_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}