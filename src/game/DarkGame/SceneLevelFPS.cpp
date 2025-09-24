#include "SceneLevelFPS.h"
#include "../../graphics/Shader.h"
#include <iostream>
#include "../../core/Transform.h"
#include "../../core/Entity.h"
#include "../Guy.h"
#include "../../core/Transform.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "../../physics/RigidBody.h"
#include "../../physics/CharacterController.h"
#include "bullet/btBulletCollisionCommon.h"
#include "../../util//MeshLoader.h"
#include "../../graphics/CameraFPS.h"
#include "../../graphics/Model.h"
#include "../../util/LoadData.h"

void mouseMovementCallback(GLFWwindow* window, double xPos, double yPos);

Shader* shader;
Entity* guy;
Entity* shotgun;
Camera* cameraFps;

MeshLoader meshLoader;
std::vector<btVector3> bulletVertices;

std::atomic<bool> loadedModels = false;


void SceneLevelFPS::init()
{
	Data::LoadData loader;
	loader.Load();

	m_engine->allLoaded = false;

	Scene::init();
	
	glfwSetCursorPosCallback(m_engine->getWindow(), mouseMovementCallback);

	std::cout << "Iniciou o level 1 \n";
	shader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

	// GUY
	guy = new Guy(shader);
	auto guyTransform = guy->transform;
	guyTransform->setPosition(glm::vec3(0, 30, -5.0));
	guy->setModel(loader.guyModel);
	guy->setName("guy");
	btCollisionShape* shape1 = new btCapsuleShape(0.3f, 1.2f);
	guy->addComponent<CharacterController>(guyTransform->position, physicalWorld, 0.3, 1.5, 1000);
	auto cc = guy->getComponent<CharacterController>();
	addEntity(guy);

	// Criando ojeto CameraFps
	cameraFps = new CameraFPS(shader, guy);
	auto camTransform = cameraFps->transform;
	camTransform->setPosition(glm::vec3(0, 1, 0.0));
	camTransform->setScale(glm::vec3(0.1, 0.1, 0.1));
	camTransform->setRotation(glm::vec3(45.0, 0.0, 0.0));
	cameraFps->setModel(loader.camModel);
	Scene::setMainCamera(cameraFps); // Seta como camera principal no jogo
	Scene::addEntity(cameraFps);
	
	// Shotgun
	shotgun = new Entity(shader, mainCamera);
	auto shotgunTransform = shotgun->getComponent<Transform>();
	shotgunTransform->setPosition(glm::vec3(-2, -1.5, 4));
	shotgunTransform->setScale(glm::vec3(3, 3, 3));
	shotgun->setModel(loader.shotgunModel);
	Scene::addEntity(shotgun);

	// GROUND
	auto ground = new Entity(shader);
	btTriangleMesh* terrainMesh = new btTriangleMesh();
	meshLoader.loadTriangles("./assets/models/ground2/ground2.obj", terrainMesh, loader.groundModel->loadedScene);
	btBvhTriangleMeshShape* terrainShape = meshLoader.createTerrainShape(terrainMesh);
	ground->addComponent<RigidBody>(ground->getComponent<Transform>()->position, terrainShape, physicalWorld, true, 0, 0.5f);
	ground->setModel(loader.groundModel);
	Scene::addEntity(ground);

	// BUNKER
	auto bunker = new Entity(shader);
	auto bunkerTransform = bunker->getComponent<Transform>();
	bunkerTransform->setPosition(glm::vec3(0, 0.2, 0));
	bunkerTransform->setScale(glm::vec3(0.5, 0.5, 0.5));
	meshLoader.loadVertices("./assets/models/ruby/ruby.obj", bulletVertices);
	btConvexHullShape* shape3 = meshLoader.createShape(bulletVertices);
	bunker->addComponent<RigidBody>(bunker->getComponent<Transform>()->position, shape3, physicalWorld, true, 0, 0.5f);
	bunker->setModel(loader.bunkerModel);
	Scene::addEntity(bunker);
	
	//Scene::init();

	Scene::startEntitys();

	m_engine->allLoaded = true;
}

void SceneLevelFPS::update(float deltaTime)
{
	Scene::update(deltaTime);
	loadData();
	//std::cout << m_engine->allLoaded << "\n";
	//mainCamera->updatePos(guy->getComponent<Transform>()->position);
	renderer->UpdateCameraView(mainCamera, shader);
	if (!mainCamera) {
		std::cerr << "mainCamera is null!" << std::endl;
		return;
	}
	//cameraFps->transform->setRotation(glm::vec3(0, 5, 0));

	guy->processKeyboard(m_engine->getWindow(), deltaTime);
	//shotgun->transform->setRotation(cameraFps->transform->rotation);
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

void SceneLevelFPS::loadData()
{

}

void mouseMovementCallback(GLFWwindow* window, double xPos, double yPos)
{
	if(guy)
		guy->updateMouseMovement(xPos, yPos);

	if (cameraFps)
		cameraFps->updateMouseMovement(xPos, yPos);

}