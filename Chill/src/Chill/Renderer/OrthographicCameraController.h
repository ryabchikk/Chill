#pragma once

#include "Chill/Renderer/OrthographicCamera.h"
#include "Chill/Core/Timestep.h"

#include "Chill/Events/ApplicationEvent.h"
#include "Chill/Events/MouseEvent.h"

namespace Chill {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void Update(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
    
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
           float m_ZoomLevel = 1.0f;
           OrthographicCamera m_Camera;

           bool m_Rotation;

           glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
           float m_CameraRotation = 0.0f;
           float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };

}

