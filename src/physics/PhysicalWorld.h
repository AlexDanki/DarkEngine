#pragma once

#include "bullet/btBulletDynamicsCommon.h"
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>

class PhysicalWorld {
public:
	PhysicalWorld();
	void physicsInit();
	void physicsShutdown();
	void setRigidBody(btRigidBody* rb);
	void setController(btKinematicCharacterController* controller);
	btDiscreteDynamicsWorld* getWorld() { return m_world; };

	void update(float deltaTime);
	void setDebugDrawer(class BulletDebugDrawer* dd);
	void debugDraw();


private:
	btBroadphaseInterface* m_broadphase;
	btCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_world;
};