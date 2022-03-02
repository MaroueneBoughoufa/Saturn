#pragma once
#include "Saturn/Core.h"

#ifdef ST_PLATFORM_WINDOWS
#include "Saturn/Input.h"

namespace Saturn
{
	class Win32Input : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
#endif