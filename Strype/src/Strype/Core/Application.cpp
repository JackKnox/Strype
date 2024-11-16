#include "stypch.h"

#include "Application.h"

#include "Strype/Core/Log.h"
#include "Strype/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Strype {
	
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		STY_PROFILE_FUNCTION();

		STY_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(STY_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		STY_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(STY_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(STY_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		STY_PROFILE_FUNCTION();

		while (m_Running)
		{
			STY_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				STY_PROFILE_SCOPE("LayerStack::OnUpdate");

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			{
			#ifdef STY_DEBUG
				STY_PROFILE_SCOPE("LayerStack::OnImGuiRender");

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			#endif // STY_DEBUG
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		STY_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}