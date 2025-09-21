#include "PhysicalWorld.h"
#include <iostream>
#include <math.h>
#include "BulletDebugDrawer.h"
#include "../graphics/Shader.h"



PhysicalWorld::PhysicalWorld()
{
	
}

void PhysicalWorld::physicsInit()
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration;
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_broadphase = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver();
	m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	m_world->setGravity(btVector3(0, -9.8f, 0));
}

void PhysicalWorld::physicsShutdown()
{
	//delete m_collisionConfiguration;
	//delete m_dispatcher;
	//delete m_broadphase;
	//delete m_solver;
	//delete m_world;
}

void PhysicalWorld::setRigidBody(btRigidBody* rb)
{
	m_world->addRigidBody(rb);
}

void PhysicalWorld::setController(btKinematicCharacterController* controller)
{
	m_world->addAction(controller);
}


void PhysicalWorld::update(float deltaTime)
{
	//btScalar dt = (float)deltaTime;
	float fixedTimeStep = 1.0f / 60.0f; // 60 Hz
	int maxSubSteps = 5;

	m_world->stepSimulation(deltaTime, maxSubSteps, fixedTimeStep);
	
	//m_world->stepSimulation(deltaTime);
}

void PhysicalWorld::setDebugDrawer(BulletDebugDrawer* dd)
{
	m_world->setDebugDrawer(dd);
	
}

void PhysicalWorld::debugDraw()
{
	for(int i = 0; i < m_world->getNumCollisionObjects(); i++ )
	{
		btCollisionObject* obj = m_world->getCollisionObjectArray()[i];
		btTransform transform = obj->getWorldTransform();
		btCollisionShape* shape = obj->getCollisionShape();

		if(shape->getShapeType() == TRIANGLE_MESH_SHAPE_PROXYTYPE)
		{
			continue;
		}
		m_world->debugDrawObject(transform, shape, btVector3(1, 0.5, 0.2));
	}
	
}
