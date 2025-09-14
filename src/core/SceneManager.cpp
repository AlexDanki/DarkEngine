#include "SceneManager.h"
#include "iostream"
#include "../graphics/Renderer.h"

SceneManager::SceneManager(Scene* curLevel)
	:m_currentScene(curLevel)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::init()
{
	if (m_currentScene) {
		m_currentScene->init();
	}
}

void SceneManager::changeScene(Scene* scene)
{
	if (m_currentScene) {
		m_currentScene->destroy();
		//delete m_currentScene;
	}

	m_currentScene = scene;

	if (m_currentScene != nullptr) {
		m_currentScene->init();
	}
}

void SceneManager::updateCurrentScene(double deltaTime)
{
	if (m_currentScene) {
		m_currentScene->update(deltaTime);
	}
	
}

void SceneManager::renderCurrentScene(Renderer* renderer)
{
	if (m_currentScene) {
		m_currentScene->render();
	}
}
