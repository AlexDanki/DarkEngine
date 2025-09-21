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
	void setRigidbody(btRigidBody* _rb) { rb = _rb; };

private:
	btRigidBody* rb;
	btScalar linearDamping;
	btScalar angularDamping;
};