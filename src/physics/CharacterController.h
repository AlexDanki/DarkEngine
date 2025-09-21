#pragma once
#include "glm/glm.hpp"
#include "../core/Component.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>


class CharacterController : public Component
{
public:
	CharacterController(glm::vec3 startPosition, class PhysicalWorld* _physicalWorld,  btScalar radius, btScalar height, btScalar stepHeight);
	~CharacterController();

	void init(glm::vec3 startPosition, class PhysicalWorld* _physicalWorld);
	void start() override;
	void update(float deltaTime) override;

	void setWalkDirection(const btVector3 direction);
	void jump();
	//bool canJump() const;

	btKinematicCharacterController* getController() const { return controller; }
	btPairCachingGhostObject* getGhostObject() const { return ghostObject; }
private:
	bool canJump;

	glm::vec3 m_startPosition;
	class PhysicalWorld* m_pw;
	btScalar m_radius;
	btScalar m_height;
	btScalar m_stepHeight;

	btCapsuleShape* capsuleShape;
	btKinematicCharacterController* controller;
	btPairCachingGhostObject* ghostObject;
};