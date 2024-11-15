#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Strype::Texture::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Strype::Timestep ts)
{
	STY_PROFILE_FUNCTION();

	// Update
	{
		STY_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		STY_PROFILE_SCOPE("Renderer Prep");
		Strype::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Strype::RenderCommand::Clear();
	}

	{
		STY_PROFILE_SCOPE("Renderer Draw");
		Strype::Renderer::BeginScene(m_CameraController.GetCamera());

		Strype::Renderer::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Strype::Renderer::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Strype::Renderer::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);

		Strype::Renderer::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Strype::Event& e)
{
	m_CameraController.OnEvent(e);
}