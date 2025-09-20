#pragma once
#include "Camera.h"

class CameraFPS : public Camera{
public:
	CameraFPS(class Shader* shader, Entity* entity);

	void processKeyBoard(GLFWwindow* window, float deltaTime) override;
};