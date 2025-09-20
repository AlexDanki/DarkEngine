#include "Transform.h"
#include "glfw/glfw3.h"
#include <iostream>
#include "../physics/RigidBody.h"
#include "bullet/btBulletCollisionCommon.h"
#include "Entity.h"
#include <vector>

Transform::Transform() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f),
	m_ownerRb(nullptr)
{

}

void Transform::start()
{
	if(m_owner->hasComponent<RigidBody>())
		m_ownerRb = m_owner->getComponent<RigidBody>()->rb;
}

void Transform::update(float deltaTime)
{
	
}

glm::mat4 Transform::getLocalMatrix()
{
	return modelMatrix();
}

glm::mat4 Transform::getGlobalMatrix()
{
	
	//std::cout << parent->getName() << "\n";
	Entity* parent = m_owner->getParent();

	if (parent)
	{
		return parent -> getComponent<Transform>()->getGlobalMatrix() * getLocalMatrix();
	}
	return getLocalMatrix();
}

glm::vec3 Transform::getFront()
{
	glm::mat4 globalMatrix = getGlobalMatrix();
	return globalMatrix[2];
}

glm::vec3 Transform::getRight()
{
	glm::mat4 globalMatrix = getGlobalMatrix();
	return globalMatrix[0];
}

glm::vec3 Transform::getUp()
{
	glm::mat4 globalMatrix = getGlobalMatrix();
	return globalMatrix[1];
}

glm::mat4 Transform::modelMatrix()
{
	
	glm::mat4 trans = glm::mat4(1.0f);

	if(m_ownerRb)
	{
		//m_owner->getComponent<RigidBody>()->hi();
		btTransform t;
		m_ownerRb->getMotionState()->getWorldTransform(t);

		btQuaternion rotation = t.getRotation();
		btVector3 translate = t.getOrigin();
		

		//std::cout << translate.getY() << " in " << m_owner-> name << "\n";

		glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.getAngle(),
			glm::vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));

		glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f),
			glm::vec3(translate.getX(), translate.getY(), translate.getZ()));

		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
		
		trans = TranslationMatrix * RotationMatrix * scaleMatrix;
	}
	else
	{
		//std::cout << "Alguém esteve aqui \n";
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, position);
		trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1.0f, 0.0, 0.0));
		trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0));
		trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0f, 0.0, 1.0f));
		trans = glm::scale(trans, scale);
		curPosition = position;
	}
	
	

	return trans;
}

glm::mat4 Transform::viewMatrix()
{
	glm::mat4 view = glm::mat4(1.0);
	view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));

	return view;
}

glm::mat4 Transform::projMatrix()
{
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 900.0f / 600.0f, 0.3f, 100.0f);
	return projection;
}
