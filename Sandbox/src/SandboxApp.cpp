#include <RetroEngine.h>
#include <ImGui/imgui.h>

class ExampleLayer : public Retro::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Retro::Input::IsKeyPressed(KEY_TAB))
		{
			Rtro_TRACE("Tab key pressed");
		}
	}

	void OnEvent(Retro::Event& event) override
	{
		if (event.GetEventType() == Retro::EventType::KeyPressed)
		{
			Retro::KeyPressedEvent& e = (Retro::KeyPressedEvent&)event;
			Rtro_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Some random text.");
		ImGui::End();
	}
};

class Sandbox : public Retro::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Retro::Application* Retro::CreateApplication()
{
	return new Sandbox();
}