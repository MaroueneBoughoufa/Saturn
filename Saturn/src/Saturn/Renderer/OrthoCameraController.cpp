#include "stpch.h"
#include "OrthoCameraController.h"

#include "Saturn/Core/Input.h"
#include "Saturn/Core/KeyCodes.h"

namespace Saturn
{
	OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation),
		m_OrthoCamera(-m_AspectRatio*m_ZoomLevel,m_AspectRatio*m_ZoomLevel,-m_ZoomLevel,m_ZoomLevel)
	{
	}

	void OrthoCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(KEY_J))
		{
			m_CameraPosition.x -=  cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
			m_CameraPosition.y -=  sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
		}
		else if (Input::IsKeyPressed(KEY_L))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
		}

		if (Input::IsKeyPressed(KEY_I))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
		}
		else if (Input::IsKeyPressed(KEY_K))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(KEY_U))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(KEY_O))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 100.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= 100.0f)
				m_CameraRotation += 360.0f,
			
			m_OrthoCamera.SetRotation(m_CameraRotation);
		}

		m_OrthoCamera.SetPosition(m_CameraPosition);
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthoCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthoCameraController::OnWindowResized));
	}

	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_OrthoCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_OrthoCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
