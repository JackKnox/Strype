#include "stypch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Strype {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		STY_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		STY_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGL();
		STY_CORE_ASSERT(status, "Failed to initialize Glad!");
		
		STY_CORE_INFO("OpenGL Info:");
		STY_CORE_INFO("   Vendor: {0}", (char*)glGetString(GL_VENDOR));
		STY_CORE_INFO("   Renderer: {0}", (char*)glGetString(GL_RENDERER));
		STY_CORE_INFO("   Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		STY_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}