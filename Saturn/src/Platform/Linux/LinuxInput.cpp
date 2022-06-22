#include "stpch.h"
#include "Saturn/Core/Core.h"

#ifdef ST_PLATFORM_LINUX
#include "Saturn/Core/Input.h"
#include "Saturn/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Saturn
{
	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto pos = GetMousePosition();
		return pos.x;
	}

	float Input::GetMouseY()
	{
		auto pos = GetMousePosition();
		return pos.y;
	}
}
#endif
