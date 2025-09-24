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

	// Guy attributes
	const float JUMP_FORCE = 5.0f;
	const float SPEED = 0.05f;
};