#include "SceneLevelFPS.h"
#include "../graphics/Shader.h"
#include <iostream>
#include "../graphics/Model.h"
#include "../core/Transform.h"
#include "../core/Entity.h"
#include "Guy.h"
#include "../core/Transform.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "../physics/RigidBody.h"
#include "bullet/btBulletCollisionCommon.h"


Model* model;
Model* groundModel;
Entity entity;
Entity* ground;
//Guy* guy;
//Guy* guy2;
Shader* shader;


void Test();

bool firstTime = true;

void SceneLevelFPS::init()
{

	//Scene::init();
	std::cout << "Iniciou o level 1 \n";
	shader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

	model = new Model("./assets/models/guy/guy.obj");
	
	groundModel = new Model("./assets/models/ground/ground.obj");
	
	for(int i = 0; i < 30; i++)
	{
		Entity* guy = new Guy(shader);
		auto guyTransform = guy->transform;
		guyTransform->setPosition(glm::vec3(i*0.1f, 3*i, 0.0));
		guy->setModel(model);
		guy->setName("guy");
		//guy->addComponent<HelloGuy>();
		btCollisionShape* shape = new btCapsuleShape(0.3f, 1.2f);
		guy->addComponent<RigidBody>(guyTransform->position, shape, physicalWorld, false, 10, 0.0);
		addEntity(guy);

	}

	ground = new Entity(shader);
	//ground.addComponent<Transform>();
	btCollisionShape* shape3 = new btBoxShape(btVector3(13.0f, 0.05f, 13.0f));
	ground->addComponent<RigidBody>(ground->getComponent<Transform>()->position, shape3, physicalWorld, true, 0, 0.5f);
	ground->setModel(groundModel);
	
	addEntity(ground);

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

	delete model;
	delete groundModel;
	//delete trans;
	//delete groundTrans;
	delete shader;
}

void Test()
{
	
}