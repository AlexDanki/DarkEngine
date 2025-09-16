#pragma once
#include "Camera.h" 

class CameraFly : public Camera {
public:
	CameraFly(glm::vec3 position = glm::vec3(0.0f, 10.0f, 30.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	CameraFly(class Shader* _shader, class Entity* _parent);

	void ProcessKeyboard(Camera_Movement direction, float deltaTime) override;

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) override;

	void ProcessScrool(double yoffset) override;

private:
};