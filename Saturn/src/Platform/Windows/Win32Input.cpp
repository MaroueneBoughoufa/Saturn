#include "stpch.h"
#include "Saturn/Core/Core.h"

#ifdef ST_PLATFORM_WINDOWS
#include "Win32Input.h"

#include "Saturn/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Saturn
{
	Scope<Input> Input::s_Instance = CreateScope<Win32Input>();

	bool Win32Input::IsKeyPressedImpl(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Win32Input::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Win32Input::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Win32Input::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float Win32Input::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
#endif
