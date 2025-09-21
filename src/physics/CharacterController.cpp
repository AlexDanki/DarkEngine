#include "CharacterController.h"
#include "PhysicalWorld.h"

CharacterController::CharacterController( glm::vec3 startPosition, PhysicalWorld* _physicalWorld, btScalar radius, btScalar height, btScalar stepHeight):
	m_startPosition(startPosition),
m_pw(_physicalWorld),
m_radius(radius),
m_height(height),
m_stepHeight(stepHeight),
capsuleShape(nullptr),
canJump(false)
{
	//init(m_startPosition, m_pw);
}

CharacterController::~CharacterController()
{
	delete capsuleShape;
	delete ghostObject;
	delete m_pw;
}

void CharacterController::init(glm::vec3 startPosition, PhysicalWorld* _physicalWorld)
{
	capsuleShape = new btCapsuleShape(m_radius, m_height - 2 * m_radius);
	ghostObject = new btPairCachingGhostObject();
	ghostObject->setCollisionShape(capsuleShape);
	ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	controller = new btKinematicCharacterController(ghostObject, capsuleShape, m_stepHeight, btVector3(0,1,0));

	btVector3 startPos = btVector3(startPosition.x, startPosition.y, startPosition.z);
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(startPos);

	ghostObject->setWorldTransform(startTransform);
	_physicalWorld->getWorld()->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

	_physicalWorld->getWorld()->addCollisionObject(ghostObject,
		btBroadphaseProxy::CharacterFilter,
		btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);

	_physicalWorld->setController(controller);
	controller->setGravity(btVector3(0, -9.8f, 0));
}

void CharacterController::start()
{
	init(m_startPosition, m_pw);
	
}

void CharacterController::update(float deltaTime)
{
	
}

void CharacterController::setWalkDirection(const btVector3 direction)
{
	controller->setWalkDirection(direction);
}

void CharacterController::jump()
{
	if(controller->canJump())
	{
		controller->jump();
	}
}




