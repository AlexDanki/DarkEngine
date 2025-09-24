#pragma once
#include "Camera.h"

class CameraFPS : public Camera{
public:
	CameraFPS(class Shader* shader, Entity* entity = nullptr);

	void update(float deltaTime) override;

	void processKeyBoard(GLFWwindow* window, float deltaTime) override;
	void updateMouseMovement(double xPos, double yPos) override;

private:
	glm::vec3 rot;
	bool firstMouse;
	double lastY;
};