#include "Guy.h"
#include <glfw/glfw3.h>
#include "../physics/CharacterController.h"
#include "../graphics/Camera.h"
#include "../core/EngineContext.h"

float angle = 0;

Guy::Guy(Shader* shader, Entity* _parent) : 
	Entity(shader, _parent),
	rb(nullptr),
	linearDamping(0.1),
	angularDamping(0.8),
	lastX(0.0),
	firstMouse(true),
	horizontalMovement(0.0)
{
	
}

void Guy::start()
{
	Entity::start();
	if(hasComponent<RigidBody>())
		rb = getComponent<RigidBody>()->rb;

	if(rb)
	{
		rb->setAngularFactor(btVector3(0, 0, 0));
		rb->setDamping(linearDamping, angularDamping);
	}
	
}

void Guy::update(float deltaTime)
{
	Entity::update(deltaTime);
	//rb->setAngularVelocity(btVector3(0, 0.1, 0));
}

void Guy::processKeyboard(GLFWwindow* window, float deltaTime)
{
	btVector3 walkDir = btVector3(0, 0, 0);
	auto cc = getComponent<CharacterController>();

	auto camera = EngineContext::get().mainCamera;

	if (!camera) return;

	btVector3 camFront = btVector3(camera->transform->getFront().x, camera->transform->getFront().y, camera->transform->getFront().z);
	
	btVector3 camRight = btVector3(camera->transform->getRight().x, camera->transform->getRight().y, camera->transform->getRight().z);
	

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		walkDir += camFront.normalized();//btVector3(0, 0, 1).normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		walkDir -= camFront.normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		walkDir += camRight.normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		walkDir -= camRight.normalized();
	}
	cc->setWalkDirection(walkDir * Guy::SPEED);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cc->jump(Guy::JUMP_FORCE);
	}
}

void Guy::updateMouseMovement(double xPos, double yPos)
{
	if(firstMouse)
	{
		lastX = xPos;
		firstMouse = false;
	}

	double xOffset = xPos - lastX;
	lastX = xPos;

	double sensitivity = 0.002;
	double angle = xOffset * sensitivity;
	getComponent<CharacterController>()->setRotation(-angle);

}
