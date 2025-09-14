#pragma once

#include "bullet/btBulletDynamicsCommon.h"

class PhysicalWorld {
public:
	PhysicalWorld();
	void physicsInit();
	void physicsShutdown();
	void setRigidBody(btRigidBody* rb);

	void update(float deltaTime);
	void setDebugDrawer(class BulletDebugDrawer* dd);
	void debugDraw(){ m_world->debugDrawWorld(); }

private:
	btBroadphaseInterface* m_broadphase;
	btCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_world;
};