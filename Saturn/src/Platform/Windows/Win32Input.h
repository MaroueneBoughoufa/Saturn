#pragma once
#include "Saturn/Core/Core.h"

#ifdef ST_PLATFORM_WINDOWS
#include "Saturn/Core/Input.h"

namespace Saturn
{
	class Win32Input : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
#endif
