#include "stypch.h"
#include "GlfwContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Strype {

	GlfwContext::GlfwContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		STY_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void GlfwContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		STY_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void GlfwContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}