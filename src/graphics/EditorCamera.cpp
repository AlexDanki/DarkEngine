#include "EditorCamera.h"
#include <iostream>
#include "../core/Engine.h"



EditorCamera::EditorCamera():
    editorCamSpeed(15)
{
    MovementSpeed = editorCamSpeed;
}

void EditorCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 world_front = glm::vec3(Front.x, 0, Front.z);
    glm::vec3 world_back = glm::vec3(Front.x, 0, Front.z);
    if (direction == FORWARD)
        Position += world_front * velocity;
    if (direction == BACKWARD)
        Position -= world_back * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void EditorCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void EditorCamera::ProcessScrool(double yoffset)
{
    float scroolSpeed = 100.0f;
    float velocity = scroolSpeed * m_engine -> m_deltaTime;
    Position += Front * velocity * (float) yoffset;
}
