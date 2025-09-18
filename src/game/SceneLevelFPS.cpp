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
#include "../util//MeshLoader.h"

Shader* shader;

void Test();
Entity* guy;

bool firstTime = true;

MeshLoader meshLoader;
std::vector<btVector3> bulletVertices;

void SceneLevelFPS::init()
{

	//Scene::init();
	std::cout << "Iniciou o level 1 \n";
	shader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");


	// GUY
	guy = new Guy(shader);
	auto guyTransform = guy->transform;
	guyTransform->setPosition(glm::vec3(0, 10, -5.0));
	auto guyModel = createModel("./assets/models/guy/guy.obj");
	guy->setModel(guyModel);
	guy->setName("guy");
	btCollisionShape* shape1 = new btCapsuleShape(0.3f, 1.2f);
	guy->addComponent<RigidBody>(guyTransform->position, shape1, physicalWorld, false, 10, 0.5);
	addEntity(guy);

	mainCamera = new Camera(shader, guy);
	auto camModel = createModel("./assets/models/camera/camera.obj");
	auto camTransform = mainCamera->transform;
	camTransform->setPosition(glm::vec3(0, 1, 0.0));
	camTransform->setScale(glm::vec3(0.1, 0.1, 0.1));
	camTransform->setRotation(glm::vec3(0.0, 0.0, 0.0));
	mainCamera->setModel(camModel);
	mainCamera->getEngine(m_engine);
	addEntity(mainCamera);

	// GUY2
	Entity* guy2 = new Guy(shader);
	auto guyTransform2 = guy2->transform;
	guyTransform2->setPosition(glm::vec3(0, 2, 0.0));
	guyTransform2->setRotation(glm::vec3(0.0, 0.0, -90.0));
	guy2->setModel(guyModel);
	guy2->setName("guy2");
	addEntity(guy2);

	//guy->removeChild(guy2);

	// GROUND
	auto groundModel = createModel("./assets/models/ground/ground.obj");
	auto ground = new Entity(shader);
	btCollisionShape* shape2 = new btBoxShape(btVector3(13, 0.01, 13));
	ground->addComponent<RigidBody>(ground->getComponent<Transform>()->position, shape2, physicalWorld, true, 0, 0.5f);
	ground->setModel(groundModel);
	addEntity(ground);

	// BUNKER
	auto bunkerModel = createModel("./assets/models/bunker/bunker.obj");
	auto bunker = new Entity(shader);
	auto bunkerTransform = bunker->getComponent<Transform>();
	bunkerTransform->setPosition(glm::vec3(0, 0.2, 0));
	bunkerTransform->setScale(glm::vec3(0.5, 0.5, 0.5));
	meshLoader.loadVertices("./assets/models/ruby/ruby.obj", bulletVertices);
	btConvexHullShape* shape3 = meshLoader.createShape(bulletVertices);
	bunker->addComponent<RigidBody>(bunker->getComponent<Transform>()->position, shape3, physicalWorld, true, 0, 0.5f);
	bunker->setModel(bunkerModel);
	addEntity(bunker);
	

	Scene::init();

}

void SceneLevelFPS::update(float deltaTime)
{
	Scene::update(deltaTime);
	//mainCamera->updatePos(guy->getComponent<Transform>()->position);
	renderer->UpdateCameraView(mainCamera, shader);
	if (!mainCamera) {
		std::cerr << "mainCamera is null!" << std::endl;
		return;
	}
	
}

void SceneLevelFPS::render()
{	
	Scene::render();
	
}

void SceneLevelFPS::destroy()
{
	Scene::destroy();

	delete shader;
}

void Test()
{
	
}