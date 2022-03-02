#include <Saturn.h>
#include <ImGui/imgui.h>

class ExampleLayer : public Saturn::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Saturn::Input::IsKeyPressed(KEY_TAB))
		{
			ST_TRACE("Tab key pressed");
		}
	}

	void OnEvent(Saturn::Event& event) override
	{
		if (event.GetEventType() == Saturn::EventType::KeyPressed)
		{
			Saturn::KeyPressedEvent& e = (Saturn::KeyPressedEvent&)event;
			ST_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Some random text.");
		ImGui::End();
	}
};

class Sandbox : public Saturn::Application
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

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}