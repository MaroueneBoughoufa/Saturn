#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Timestep.h"

#include "Saturn/Events/Event.h"
#include "Saturn/Events/ApplicationEvent.h"

#include "Saturn/Renderer/Renderer.h"

#include "Saturn/ImGui/ImGuiLayer.h"

namespace Saturn
{
	int Main(int agrc, char* argv[]);
}

namespace Saturn
{
	class Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();
		
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;

		friend int Saturn::Main(int argc, char* argv[]);
	};

	// To be defined in client
	Application* CreateApplication();
}
