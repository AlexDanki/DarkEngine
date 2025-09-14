#include "Engine.h"
#include "../core/Entity.h"
#include <iostream>
#include "../graphics/Camera.h"
#include <glfw/glfw3.h>
#include "../graphics/Renderer.h"
#include "./Scene.h"
#include "../graphics/Skybox.h"
#include "../graphics/Shader.h"
#include "../physics/PhysicalWorld.h"
#include "../graphics/Model.h"

//Renderer* renderer;
Skybox* skybox;
Shader* skyShader;

bool showDebugDrawer = false;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

unsigned int cubmapTexture;

Scene::Scene(Engine* engine) :
	m_engine(engine),
	m_updatingEntities(false),
	mainCamera(nullptr),
	renderer(nullptr),
	physicalWorld(nullptr)
{ 
	m_engine->addScenes(this); 
	physicalWorld = new PhysicalWorld();
	physicalWorld->physicsInit();
	
}

void Scene::init()
{
	glfwSetKeyCallback(m_engine->getWindow(), keyCallback);

	mainCamera = new Camera();
	renderer = new Renderer();
	renderer->init();
	skybox = new Skybox();
	skybox->setupMesh();
	skyShader = new Shader("./shaders/skybox.vert", "./shaders/skybox.frag");

	std::string folder = "skybox3";
	std::vector<std::string> faces =
	{
		"./assets/textures/"+ folder +"/right.jpg",
		"./assets/textures/"+ folder +"/left.jpg",
		"./assets/textures/"+ folder +"/top.jpg",
		"./assets/textures/"+ folder +"/bottom.jpg",
		"./assets/textures/"+ folder +"/front.jpg",
		"./assets/textures/"+ folder +"/back.jpg"
	};

	cubmapTexture = skybox->loadCubeMap(faces);

	for(auto& pair : renderGroups)
	{
		for(Entity* e : pair.second)
		{
			e->start();
		}
		std::cout << pair.second.size() << " \n";
	}
	
	physicalWorld->setDebugDrawer(renderer->getDebugDrawer());
}

void Scene::update(float deltaTime)
{
	physicalWorld->update(deltaTime);
	m_updatingEntities = true;

	for (auto& pair : renderGroups)
	{
		for (Entity* e : pair.second)
		{
			if(e->m_state == E_ACTIVE)
				e->update(deltaTime);
		}
	}

	m_updatingEntities = false;

	if (!m_penddingEntities.empty()) {

		for (Entity* e : m_penddingEntities) {
			addEntity(e);
		}

		m_penddingEntities.clear();
	}


	for(auto& pair : renderGroups)
	{
		auto& vec = pair.second;

		for(Entity* e : vec)
		{
			if (e->m_state == E_State::E_DEAD)
			{
				delete e;
				std::cout << "deletado!!!";
			}	
		}

		vec.erase(
			std::remove_if(vec.begin(), vec.end(),
				[](Entity* e) {
					return e->m_state == E_State::E_DEAD;
				}), vec.end()
		);

	}

}

void Scene::render()
{
	renderer->drawEntityes(renderGroups);
	renderer->drawSkybox(skyShader, skybox, mainCamera, cubmapTexture);

	{ // Renderiza os colisores da cena - Deve vir depois dos outros renders 
		if(showDebugDrawer)
		{
			physicalWorld->debugDraw();
			renderer->drawCollisors(mainCamera);
		}
	}
}

void Scene::destroy()
{
	physicalWorld->physicsShutdown();

	int countDeleteds = 0;
	for(auto m : m_models)
	{
		delete m;
		countDeleteds++;
		std::cout << countDeleteds << " modelo(s) deletados... \n";
	}

	m_models.clear();

	delete skybox;
	delete skyShader;
	delete renderer;
	delete mainCamera;
	delete physicalWorld;
}

void Scene::addEntity(Entity* entity)
{
	if(entity->hasAShader())
	{
		if (!m_updatingEntities) {
			renderGroups[entity->getShader()].push_back(entity);
		}
		else {
			m_penddingEntities.push_back(entity);
		}
	}
	else {
		std::cerr << "Entity has no shader assigned!" << std::endl;
	}

}

void Scene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		mainCamera->ProcessKeyboard(Camera_Movement::FORWARD, m_engine->m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(Camera_Movement::BACKWARD, m_engine->m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(Camera_Movement::LEFT, m_engine->m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera->ProcessKeyboard(Camera_Movement::RIGHT, m_engine->m_deltaTime);
}

Model* Scene::createModel(std::string path)
{
	Model* model = new Model(path.c_str());
	m_models.push_back(model);
	return model;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
		showDebugDrawer = !showDebugDrawer;
	}
}
