#pragma once

#include "Saturn/Core/Layer.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/ApplicationEvent.h"

namespace Saturn
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
