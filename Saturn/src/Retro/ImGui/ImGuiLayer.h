#pragma once

#include "Retro/Layer.h"
#include "Retro/Events/MouseEvent.h"
#include "Retro/Events/KeyEvent.h"
#include "Retro/Events/ApplicationEvent.h"

namespace Retro
{
	class RETRO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}