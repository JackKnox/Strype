#include "stypch.h"
#include "GlfwInput.h"

#include "Strype/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Strype {

	bool GlfwInput::IsKeyOnImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GlfwInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int currentState = glfwGetKey(window, keycode);
		int previousState = m_KeyStates.count(keycode) ? m_KeyStates[keycode] : GLFW_RELEASE;

		m_KeyStates[keycode] = currentState;

		return currentState == GLFW_PRESS && previousState == GLFW_RELEASE;
	}

	bool GlfwInput::IsKeyReleasedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int currentState = glfwGetKey(window, keycode);
		int previousState = m_KeyStates.count(keycode) ? m_KeyStates[keycode] : GLFW_RELEASE;

		m_KeyStates[keycode] = currentState;

		return currentState == GLFW_RELEASE && previousState == GLFW_PRESS;
	}

	bool GlfwInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GlfwInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float GlfwInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float GlfwInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

}