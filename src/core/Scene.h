#pragma once
#include <map>
#include <vector>
#include "../graphics/Camera.h"
#include <string>


class Scene {
public:
	Scene(class Engine* engine);

	Camera* mainCamera;
	virtual void init() = 0;
	virtual void update(float deltaTime);
	virtual void render();
	virtual void destroy();
	void addEntity(class Entity* entity);
	void processInput(class GLFWwindow* window);
	class Renderer* getRenderer()const { return renderer; }

protected:
	std::vector<class Entity*> m_entities;
	std::vector<class Entity*> m_penddingEntities;
	class Engine* m_engine;
	std::map<class Shader*, std::vector<class Entity*>> renderGroups;
	bool m_updatingEntities;
	class Renderer* renderer;
	class PhysicalWorld* physicalWorld;
	std::vector<class Model* > m_models;

	class Model* createModel(std::string path);
	
};
