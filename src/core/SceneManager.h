#pragma once
#include "Scene.h"


class SceneManager {
public:
	SceneManager(Scene* curLevel);
	~SceneManager();
	void init();
	void changeScene(Scene* scene);
	void updateCurrentScene(double deltaTime);
	void renderCurrentScene(class Renderer* renderer);
	Scene* getCurrentScene() { return m_currentScene; }

private:
	Scene* m_currentScene;
};
