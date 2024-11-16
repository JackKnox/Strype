#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <sndfile/sndfile.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	STY_PROFILE_FUNCTION();

	m_CheckerboardTexture = Strype::Texture::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	STY_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Strype::Timestep ts)
{
	STY_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	// Render
	Strype::Renderer::ResetStats();
	Strype::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Strype::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += ts * 50.0f;

	Strype::Renderer::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Strype::Renderer::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Strype::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Strype::Renderer::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}

void Sandbox2D::OnEvent(Strype::Event& e)
{
	m_CameraController.OnEvent(e);
}