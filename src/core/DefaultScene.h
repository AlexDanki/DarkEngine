#pragma once
#include "Scene.h"
//#include "Triangle.h"
#include "Engine.h"

class DefaultScene : public Scene {
public:
	DefaultScene(Engine* engine): Scene(engine) {};

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void destroy() override;

private:
	//Triangle* triangle;
};
