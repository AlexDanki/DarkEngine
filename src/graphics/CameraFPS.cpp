#include "CameraFPS.h"
#include <glm/glm.hpp>

CameraFPS::CameraFPS(Shader* shader, Entity* entity):
	Camera(shader, entity)
{
}

void CameraFPS::update(float deltaTime)
{
    transform->setRotation(rot);
}

void CameraFPS::processKeyBoard(GLFWwindow* window,  float deltaTime)
{

	
}

// membro da classe CameraFPS
float pitch = 0.0f;

void CameraFPS::updateMouseMovement(double xPos, double yPos)
{
    if (firstMouse)
    {
        lastY = yPos;
        firstMouse = false;
    }

    double yOffset = yPos - lastY;
    lastY = yPos;

    float sensitivity = 0.1f;
    pitch -= static_cast<float>(yOffset) * sensitivity;

    // Limita o pitch para evitar que a câmera vire completamente
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    // Aplica a rotação acumulada
    rot = glm::vec3(-pitch, 0.0f, 0.0f);
}
