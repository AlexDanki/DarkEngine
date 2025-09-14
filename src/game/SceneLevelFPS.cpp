#include "SceneLevelFPS.h"
#include "../graphics/Shader.h"
#include <iostream>
#include "../core/Transform.h"
#include "../core/Entity.h"
#include "Guy.h"
#include "../core/Transform.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "../physics/RigidBody.h"
#include "bullet/btBulletCollisionCommon.h"

Shader* shader;

void Test();

bool firstTime = true;

void SceneLevelFPS::init()
{

	//Scene::init();
	std::cout << "Iniciou o level 1 \n";
	shader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");


	// GUY'S
	auto guyModel = createModel("./assets/models/guy/guy.obj");
	for(int i = 0; i < 30; i++)
	{
		Entity* guy = new Guy(shader);
		auto guyTransform = guy->transform;
		guyTransform->setPosition(glm::vec3(i*0.1f, 3*i, 0.0));
		guy->setModel(guyModel);
		guy->setName("guy");
		//guy->addComponent<HelloGuy>();
		btCollisionShape* shape1 = new btCapsuleShape(0.3f, 1.2f);
		guy->addComponent<RigidBody>(guyTransform->position, shape1, physicalWorld, false, 10, 0.5);
		addEntity(guy);

	}

	// GROUND
	auto groundModel = createModel("./assets/models/ground/ground.obj");
	auto ground = new Entity(shader);
	btCollisionShape* shape2 = new btBoxShape(btVector3(13.0f, 0.05f, 13.0f));
	ground->addComponent<RigidBody>(ground->getComponent<Transform>()->position, shape2, physicalWorld, true, 0, 0.5f);
	ground->setModel(groundModel);
	addEntity(ground);

	// BUNKER
	auto bunkerModel = createModel("./assets/models/bunker/bunker.obj");
	auto bunker = new Entity(shader);
	auto bunkerTransform = bunker->getComponent<Transform>();
	bunkerTransform->setPosition(glm::vec3(0, 0.2, 0));
	bunkerTransform->setScale(glm::vec3(0.5, 0.5, 0.5));
	btCollisionShape* shape3 = new btBoxShape(btVector3(1.5f, 0.5f, 1.5f));
	bunker->addComponent<RigidBody>(bunker->getComponent<Transform>()->position, shape3, physicalWorld, true, 0, 0.5f);
	bunker->setModel(bunkerModel);
	addEntity(bunker);
	

	Scene::init();

}

void SceneLevelFPS::update(float deltaTime)
{
	Scene::update(deltaTime);
}

void SceneLevelFPS::render()
{	
	Scene::render();
	renderer->UpdateCameraView(mainCamera, shader);
	
}

void SceneLevelFPS::destroy()
{
	Scene::destroy();

	delete shader;
}

void Test()
{
	
}