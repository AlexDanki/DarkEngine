#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/euler_angles.hpp>


//typedef bool GLboolean;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;

class Camera {
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;

	Camera(glm::vec3 position = glm::vec3(0.0f, 10.0f, 30.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	
	glm::mat4 getViewMatrix();

	void getEngine(class Engine* _engine) { m_engine = _engine; };

	virtual void ProcessKeyboard(Camera_Movement direction, float deltaTime) = 0;

	virtual void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) = 0;

	virtual void ProcessScrool(double yoffset) = 0;

protected:
	class Engine* m_engine = nullptr;
	void updateCameraVectors();

};
