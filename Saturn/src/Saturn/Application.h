#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Saturn/Window.h"
#include "Saturn/ImGui/ImGuiLayer.h"
#include "Saturn/Renderer/Shader.h"
#include "Saturn/Renderer/Buffer.h"
#include "Saturn/Renderer/VertexArray.h"
#include "Saturn/Renderer/OrthoCamera.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;

		OrthoCamera m_Camera;

		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}
