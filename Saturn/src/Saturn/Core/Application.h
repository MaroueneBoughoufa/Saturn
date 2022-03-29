#pragma once

#include "Core.h"
#include "LayerStack.h"

#include "Saturn/Events/Event.h"
#include "Saturn/Events/ApplicationEvent.h"

#include "Window.h"
#include "Saturn/ImGui/ImGuiLayer.h"

#include "Timestep.h"

namespace Saturn
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}
