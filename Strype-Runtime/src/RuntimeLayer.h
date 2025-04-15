#pragma once

#include <Strype.h>

namespace Strype {

	constexpr float CAMERA_WIDTH = 1280.0f;
	constexpr float CAMERA_HEIGHT = 720.0f;
	constexpr float ASPECT_RATIO = CAMERA_WIDTH / CAMERA_HEIGHT;

	class RuntimeLayer : public Layer
	{
	public:
		RuntimeLayer();
		~RuntimeLayer();

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;

		void OpenProject(const std::filesystem::path& path);
	private:
		Ref<Room> m_Room;
		Camera m_RuntimeCamera{ -ASPECT_RATIO, ASPECT_RATIO, -1, 1 };
	};

}