#pragma once
#include "../core/Entity.h"
#include "bullet/btBulletCollisionCommon.h"

class Guy : public Entity
{
public:
	Guy(class Shader* shader = nullptr, Entity* _parent = nullptr);
	void start() override;
	void update(float deltaTime) override;
	void processKeyboard(GLFWwindow* window, float deltaTime) override;
	void updateMouseMovement(double xPos, double yPos) override;
	void setRigidbody(btRigidBody* _rb) { rb = _rb; };

private:
	double horizontalMovement;
	double lastX;
	bool firstMouse;
	btRigidBody* rb;
	btScalar linearDamping;
	btScalar angularDamping;
};