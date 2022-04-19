#include <Saturn.h>
#include <Saturn/Core/EntryPoint.h>

//#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}
