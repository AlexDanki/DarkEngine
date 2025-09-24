#pragma once
#include "../graphics/Camera.h"
#include "../game/Game.h"

class EngineContext
{
public:
	Camera* mainCamera = nullptr;
	GLFWwindow* window = nullptr;
	Engine* curGame = nullptr;


	static EngineContext& get()
	{
		static EngineContext instance;
		return instance;
	}


	// Set's
	void setMainCamera(Camera* camera) { mainCamera = camera; };
	void setWindow(GLFWwindow* _window) { window = _window; };
	void setCurGame(Engine* game) { curGame = game; }

private:
	EngineContext(){}
};