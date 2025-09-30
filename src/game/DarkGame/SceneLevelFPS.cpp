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
Shader* lightShader;
Entity* guy;
Entity* shotgun;
Camera* cameraFps;

MeshLoader meshLoader;
std::vector<btVector3> bulletVertices;

std::atomic<bool> loadedModels = false;


void SceneLevelFPS::init()
{
	Data::LoadData* loader = m_engine->getLoader();
	//loader.Load();

	m_engine->allLoaded = false;

	Scene::init();
	
	glfwSetCursorPosCallback(m_engine->getWindow(), mouseMovementCallback);

	std::cout << "Iniciou o level 1 \n";

	// /!\ LEMBRAR DE SEMPRE FAZER UP DE VIEW DA CÂMERA PARA CADA NOVO SHADER
	shader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	lightShader = new Shader("./shaders/vertex.glsl", "./shaders/lightShader.frag");

	if(loader->AllDataLoaded())
	{
		// GUY
		guy = new Guy(shader);
		auto guyTransform = guy->transform;
		guyTransform->setPosition(glm::vec3(5, 0.5, -5.0));
		//guy->setModel(loader.guyModel);
		guy->setName("guy");
		btCollisionShape* shape1 = new btCapsuleShape(3.0f, 3.5f);
		guy->addComponent<CharacterController>(guyTransform->position, physicalWorld, 0.3, 1.5, 0.2);
		auto cc = guy->getComponent<CharacterController>();
		addEntity(guy);

		// CameraFps
		cameraFps = new CameraFPS(shader, guy);
		auto camTransform = cameraFps->transform;
		camTransform->setPosition(glm::vec3(0, 0.5, -0.3));
		camTransform->setScale(glm::vec3(0.1, 0.1, 0.1));
		camTransform->setRotation(glm::vec3(45.0, 0.0, 0.0));
		//cameraFps->setModel(loader.camModel);
		Scene::setMainCamera(cameraFps); // Seta como camera principal no jogo
		Scene::addEntity(cameraFps);

		// SHOTGUN
		shotgun = new Entity(shader, mainCamera);
		auto shotgunTransform = shotgun->getComponent<Transform>();
		shotgunTransform->setPosition(glm::vec3(-1.2, -1.2, 2.8));
		shotgunTransform->setScale(glm::vec3(1.5, 1.5, 1.5));
		Model* shotgunModel = Scene::createModel(loader->shotgunScene, loader->shotgunModelPath);
		shotgun->setModel(shotgunModel);
		Scene::addEntity(shotgun);

		// GROUND
		auto ground = new Entity(shader);
		btTriangleMesh* terrainMesh = new btTriangleMesh();
		meshLoader.loadTriangles("./assets/models/ground2/ground2.obj", terrainMesh, loader->groundScene);
		btBvhTriangleMeshShape* terrainShape = meshLoader.createTerrainShape(terrainMesh);
		ground->addComponent<RigidBody>(ground->getComponent<Transform>()->position, terrainShape, physicalWorld, true, 0, 0.5f);
		Model* goundModel = Scene::createModel(loader->groundScene, loader->groundModelPath);
		ground->setModel(goundModel);
		Scene::addEntity(ground);

		// BUNKER
		auto bunker = new Entity(shader);
		auto bunkerTransform = bunker->getComponent<Transform>();
		bunkerTransform->setPosition(glm::vec3(-2.0, 0.2, 0));
		bunkerTransform->setScale(glm::vec3(0.2, 0.2, 0.2));
		meshLoader.loadVertices("./assets/models/ruby/ruby.obj", bulletVertices);
		btConvexHullShape* shape3 = meshLoader.createShape(bulletVertices);
		bunker->addComponent<RigidBody>(bunker->getComponent<Transform>()->position, shape3, physicalWorld, true, 0, 0.5f);
		Model* bunkerModel = Scene::createModel(loader->bunkerScene, loader->bunkerModelPath);
		bunker->setModel(bunkerModel);
		Scene::addEntity(bunker);

		// BUILD
		auto build = new Entity(shader);
		btTriangleMesh* terrainMesh2 = new btTriangleMesh();
		meshLoader.loadTriangles("./assets/models/build/build.obj", terrainMesh2, loader->buildScene);
		btBvhTriangleMeshShape* buildShape = meshLoader.createTerrainShape(terrainMesh2);
		build->addComponent<RigidBody>(build->getComponent<Transform>()->position, buildShape, physicalWorld, true, 0, 0.5f);
		Model* buildModel = Scene::createModel(loader->buildScene, loader->buildModelPath);
		build->setModel(buildModel);
		Scene::addEntity(build);


		//LIGHT1
		auto light = new Entity(lightShader);
		auto lightTransform = light->getComponent<Transform>();
		lightTransform->setPosition(glm::vec3(-1.3, 2.75, 0.0));
		lightTransform->setScale(glm::vec3(0.06, 0.06, 0.06));
		Model* lightModel = Scene::createModel(loader->lightScene, loader->lightModelPath);
		light->setModel(lightModel);
		Scene::addEntity(light);

	}
	
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
	renderer->UpdateCameraView(mainCamera, lightShader);
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
	//std::cerr << "SceneFPS drawnning...\n";
}

void SceneLevelFPS::destroy()
{
	Scene::destroy();

	delete shader;
	delete lightShader;
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