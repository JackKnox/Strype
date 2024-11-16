#pragma once

#include <Strype.h>

class Sandbox2D : public Strype::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Strype::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Strype::Event& e) override;
private:
	Strype::CameraController m_CameraController;

	Strype::Ref<Strype::Framebuffer> m_Framebuffer;

	Strype::Ref<Strype::Texture> m_CheckerboardTexture;
};