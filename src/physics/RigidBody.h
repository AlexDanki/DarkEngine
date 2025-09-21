#pragma once
#include "bullet/btBulletDynamicsCommon.h"
#include "../core/Component.h"
#include "glm/glm.hpp"
#include <iostream>

class RigidBody : public Component {
public:
	RigidBody(const glm::vec3 position, btCollisionShape* shape = new btBoxShape(btVector3(1, 1, 1)), class PhysicalWorld* pw = nullptr, bool staticObject = false, btScalar mass = 1, btScalar bounceness = 0.0);

	btCollisionShape* m_shape;
	btDefaultMotionState* m_motionState;
	btVector3 m_position;
	btScalar m_mass;
	btScalar m_bounceness;
	btVector3 m_inertia;
	btRigidBody* rb;
	

	void init();

	void start() override;
	void update(float deltaTime) override;
	void hi() { std::cout << "Hi i'm a rigidbody !!!\n"; }
	btVector3 toBtVec3(const glm::vec3& v);
	//void setStatic(bool _static) { m_isStatic = _static; }
	

private:
	class PhysicalWorld* m_pw;
	bool m_isStatic;
};