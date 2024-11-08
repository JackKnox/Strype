#pragma once

#include <GLFW/glfw3.h>

#include "Strype/Window.h"
#include "Strype/Renderer/GraphicsContext.h"

namespace Strype {

	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(const WindowProps& props);
		virtual ~GlfwWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}