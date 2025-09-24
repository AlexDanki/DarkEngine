#include "Camera.h"
#include "Shader.h"


Camera::Camera(Shader* _shader, Entity* _parent):
    Entity(_shader, _parent)
{
    Position = glm::vec3(0, 4, -1);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = YAW;
    Pitch = PITCH;
    //updateCameraVectors();
}

void Camera::updatePos(glm::vec3 pos)
{
    Position = pos;
}

glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 globalMatrix = getComponent<Transform>()->getGlobalMatrix();
    glm::vec3 pos = glm::vec3(globalMatrix[3].x, globalMatrix[3].y, globalMatrix[3].z);
    return glm::lookAt(pos, pos + transform->getFront(), transform->getUp());
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    //Up = glm::normalize(glm::cross(Right, Front));
}
