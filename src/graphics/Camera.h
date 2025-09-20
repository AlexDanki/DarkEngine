#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../core/Entity.h"
#include "glfw/glfw3.h"
//#include <glm/gtx/euler_angles.hpp>


//typedef bool GLboolean;

const float YAW = -90.0f;
const float PITCH = 0.0f;


class Camera : public Entity{
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;


	//Camera(glm::vec3 position = glm::vec3(0.0f, 10.0f, 30.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(class Shader* _shader, class Entity* _parent = nullptr);
	glm::mat4 getViewMatrix();

	void getEngine(class Engine* _engine) { m_engine = _engine; };
	void updatePos(glm::vec3 pos);

	virtual void processKeyBoard(GLFWwindow* window, float deltaTime) = 0;

protected:
	class Engine* m_engine = nullptr;
	void updateCameraVectors();

};
