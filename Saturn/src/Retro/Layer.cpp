#include "retropch.h"

#include "Layer.h"

namespace Retro
{
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Layer::~Layer()
	{
	}
}