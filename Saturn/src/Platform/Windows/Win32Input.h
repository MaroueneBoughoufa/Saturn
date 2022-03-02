#pragma once
#include "Retro/Core.h"

#ifdef Rtro_PLATFORM_WINDOWS
#include "Retro/Input.h"

namespace Retro
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