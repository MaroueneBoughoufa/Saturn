#pragma once

#include "Saturn/Renderer/OrthoCamera.h"
#include "Saturn/Core/Timestep.h"

#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/Events/KeyEvent.h"

namespace Saturn
{
	struct CameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthoCamera& GetCamera() { return m_OrthoCamera; }
		const OrthoCamera& GetCamera() const { return m_OrthoCamera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		const CameraBounds& GetBounds() const { return m_Bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_Rotation;
		CameraBounds m_Bounds;
		OrthoCamera m_OrthoCamera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraSpeed = 2.5f;
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 60.0f;
	};
}
