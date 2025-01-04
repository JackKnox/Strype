#include "stypch.h"
#include "Strype/Core/Window.h"

#ifdef STY_PLATFORM_WINDOWS
	#include "API/GLFW/GlfwWindow.h"
#endif

namespace Strype
{
	Ref<Window> Window::Create(const WindowProps& props)
	{
#ifdef STY_PLATFORM_WINDOWS
		return CreateRef<GlfwWindow>(props);
#else
		STY_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}