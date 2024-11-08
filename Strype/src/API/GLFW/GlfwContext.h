#pragma once

#include "Strype/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Strype {

	class GlfwContext : public GraphicsContext
	{
	public:
		GlfwContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}