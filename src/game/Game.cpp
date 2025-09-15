#include "Game.h"
#include <iostream>
#include "Triangle.h"
#include "../graphics/Shader.h"
#include "SceneLevelFPS.h"
#include "../core/Scene.h"
#include "../graphics/Camera.h"
#include "../core/Window.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scrool_callback(GLFWwindow* window, double xoffset, double yoffset);

Scene* curScene;
Camera* camera;
bool firstMouse = true;
WindowInfo ws;
float lastX =  ws.Width/ 2.0f;
float lastY = ws.Height / 2.0f;

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
	glfwSetCursorPosCallback(m_window, mouse_callback);
	glfwSetScrollCallback(m_window, scrool_callback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	sceneManager->changeScene(new SceneLevelFPS(this));
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
	sceneManager->getCurrentScene()->processInput(m_window);
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


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

void scrool_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessScrool(yoffset);
}
