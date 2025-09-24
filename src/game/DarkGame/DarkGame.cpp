
#include "../../core/EngineContext.h"
#include "DarkGame.h"
#include "SceneLevelFPS.h"

//Scene* sceneFPS;

void DarkGame::run()
{
	Engine::run();
	update();
	render();
}

void DarkGame::init()
{
	Engine::init();
	start();
	//sceneFPS = new SceneLevelFPS(this);
	//sceneManager->getCurrentScene()->init();
}

void DarkGame::processInput()
{
	Engine::processInput();
}

void DarkGame::update()
{
	Engine::update();

	//sceneManager->changeScene(new SceneLevelFPS(this));
}

void DarkGame::render()
{
	Engine::render();
}

void DarkGame::draw()
{
}

void DarkGame::start()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//EngineContext::get().setCurGame(this);
	sceneManager->changeScene(new SceneLevelFPS(this));
	
}

void DarkGame::shutdown()
{
	sceneManager->getCurrentScene()->destroy();
	Engine::shutdown();
}
