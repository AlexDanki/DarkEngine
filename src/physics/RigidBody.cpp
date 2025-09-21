#include "RigidBody.h"
#include "./PhysicalWorld.h"
#include <iostream>
#include "../graphics//Mesh.h"
#include <vector>

RigidBody::RigidBody(const glm::vec3 position, btCollisionShape* shape, PhysicalWorld* pw, bool staticObject, btScalar mass, btScalar bounceness) :
	m_shape(shape),
	m_motionState(nullptr),
	m_position(btVector3(0, 0, 0)),
	m_mass(mass),
	m_inertia(btVector3(0, 0, 0)),
	rb(nullptr),
	m_pw(pw),
	m_isStatic(staticObject),
	m_bounceness(bounceness)
{
	m_position = btVector3(position.x, position.y, position.z);
	init();
}

void RigidBody::init()
{

	m_motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), m_position));
	if(m_mass > 0)
	{
		m_shape->calculateLocalInertia(m_mass, m_inertia);
	}
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(m_mass, m_motionState, m_shape, m_inertia);
	rb = new btRigidBody(shapeRigidBodyCI);
	rb->setRestitution(m_bounceness);
	rb->setFriction(1.0f);

	if (m_isStatic)
	{
		rb->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	}
	else
	{
		rb->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
	}
	m_pw->setRigidBody(rb);
	
}

void RigidBody::start()
{
}

void RigidBody::update(float deltaTime)
{
}

btVector3 RigidBody::toBtVec3(const glm::vec3& v)
{
	return btVector3(v.x, v.y, v.z);
}
