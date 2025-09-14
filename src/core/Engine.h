#pragma once
#include <GLFW/glfw3.h>
#include "SceneManager.h"
#include "../graphics/Renderer.h"
#include <memory>
#include <vector>
#include <string> 

class Engine {
public:
	Engine();
	~Engine();
	double m_deltaTime;
	virtual void init();
	void run();
	virtual void shutdown();
	void addScenes(class Scene* scene);
	void setWindowGameName(std::string _nameWindow) { m_nameWindow = _nameWindow; };
	GLFWwindow* getWindow() const { return m_window; }

protected:
	bool isRunning;
	std::string m_nameWindow = "Game Engine";
	class Scene* defaultScene;
	std::vector<Scene*> scenes;
	GLFWwindow* m_window;
	SceneManager* sceneManager;
	Renderer* renderer;
	class PhysicalWorld* physicalWorld;

	virtual void start();
	virtual void processInput();
	virtual void update();
	virtual void render();
	virtual void draw();
};
