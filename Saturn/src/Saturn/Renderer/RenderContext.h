#pragma once
#include "stpch.h"

namespace Saturn
{
	class RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}