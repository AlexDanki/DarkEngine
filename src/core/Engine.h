#pragma once
#include <GLFW/glfw3.h>
#include "SceneManager.h"
#include "../graphics/Renderer.h"
#include <memory>
#include <vector>
#include <string> 
#include "../util/LoadData.h"

class Engine {
public:
	Engine();
	~Engine();

	bool allLoaded;
	double m_deltaTime;


	virtual void init();
	void run();
	virtual void shutdown();
	void addScenes(class Scene* scene);
	void setWindowGameName(std::string _nameWindow) { m_nameWindow = _nameWindow; };
	GLFWwindow* getWindow() const { return m_window; }
	Data::LoadData* getLoader() const { return loader; };

protected:
	
	bool isRunning;
	std::string m_nameWindow = "Game Engine";
	class Scene* defaultScene;
	std::vector<Scene*> scenes;
	GLFWwindow* m_window;
	GLFWmonitor* m_monitor;
	GLFWwindow* loader_window;
	SceneManager* sceneManager;
	Renderer* renderer;
	class PhysicalWorld* physicalWorld;
	uint32_t m_ticksCount;
	Data::LoadData* loader;

	virtual void start();
	virtual void processInput();
	virtual void update();
	virtual void render();
	virtual void draw();
};
