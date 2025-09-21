#include "Guy.h"
#include <glfw/glfw3.h>
#include "../physics/CharacterController.h"

float angle = 0;

Guy::Guy(Shader* shader, Entity* _parent) : 
	Entity(shader, _parent),
	rb(nullptr),
	linearDamping(0.1),
	angularDamping(0.8)
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
	float spd = 0.05;
	btVector3 walkDir = btVector3(0, 0, 0);
	auto cc = getComponent<CharacterController>();
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		walkDir += btVector3(0, 0, 1).normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		walkDir += btVector3(0, 0, -1).normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		walkDir += btVector3(1, 0, 0).normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		walkDir += btVector3(-1, 0, 0).normalized();
	}
	cc->setWalkDirection(walkDir * spd);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cc->jump();
	}

	if (!rb) return;
	glm::mat4 globalMatrix = getComponent<Transform>()->getGlobalMatrix();
	glm::vec3 pos = glm::vec3(globalMatrix[3].x, globalMatrix[3].y, globalMatrix[3].z);
	//btRigidBody* rb = getComponent<RigidBody>()->rb;
	
	btVector3 newPosition = btVector3(pos.x, pos.y, pos.z);
	float speed = 3;

	btVector3 currentVelocity = rb->getLinearVelocity();
	btVector3 moveDirection(0, currentVelocity.getY(), 0);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		btVector3 forward = btVector3(transform->getFront().x, transform->getFront().y, transform->getFront().z);
		moveDirection += forward.normalized() * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		btVector3 backward = btVector3(transform->getFront().x, transform->getFront().y, transform->getFront().z);
		moveDirection -= backward.normalized() * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		btVector3 left = btVector3(transform->getRight().x, transform->getRight().y, transform->getRight().z);
		moveDirection += left.normalized() * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		btVector3 right = btVector3(transform->getRight().x, transform->getRight().y, transform->getRight().z);
		moveDirection -= right.normalized() * speed;
	}
	rb->activate(true);
	rb->setLinearVelocity(moveDirection);
}
