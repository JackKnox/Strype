#pragma once

#include "Strype/Sub Modules/Input/Input.h"

namespace Strype {

	class GlfwInput : public Input
	{
	protected:
		virtual bool IsKeyOnImpl(int keycode) override;
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsKeyReleasedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	private:
		std::unordered_map<int, int> m_KeyStates;
	};

}