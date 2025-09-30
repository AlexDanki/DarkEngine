#include "Game.h"
#include <iostream>
#include "Triangle.h"
#include "../graphics/Shader.h"
//#include "SceneLevelFPS.h"
#include "../core/Scene.h"
#include "../graphics/Camera.h"
#include "../core/Window.h"

Scene* curScene;
Camera* camera;
bool firstMouse = true;
//WindowInfo ws;
//float lastX =  ws.Width/ 2.0f;
//float lastY = ws.Height / 2.0f;

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::start()
{
	//Engine::start();
	//sceneManager->getCurrentScene()->init();
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//sceneManager->changeScene(new SceneLevelFPS(this));
	//sceneManager->getCurrentScene()->init();
	camera = sceneManager->getCurrentScene()->mainCamera;
}

void Game::run()
{
	Engine::run();
	update();
	render();
}

void Game::init()
{
	Engine::init();
	start();
}

void Game::processInput()
{
	Engine::processInput();
	//sceneManager->getCurrentScene()->processInput(m_window);
}

void Game::update()
{
	Engine::update();
	sceneManager->updateCurrentScene(m_deltaTime);
}

void Game::render()
{
	Engine::render();
	sceneManager->renderCurrentScene(renderer);
}

void Game::draw()
{
	//triangle->draw();
}

void Game::shutdown()
{
	sceneManager->getCurrentScene()->destroy();
	Engine::shutdown();
	
}

