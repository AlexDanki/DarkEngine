#pragma once
#include "Camera.h" 

class EditorCamera : public Camera {
public:
	EditorCamera();


	void ProcessKeyboard(Camera_Movement direction, float deltaTime) override;

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) override;

	void ProcessScrool(double yoffset) override;

private:
	float editorCamSpeed;
};
