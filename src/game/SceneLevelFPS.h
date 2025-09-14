#pragma once
#include "../core/Scene.h"
#include "Triangle.h"
#include "../core/Engine.h"

class SceneLevelFPS : public Scene {
public:
	SceneLevelFPS(Engine* engine): Scene(engine),triangle(nullptr) {};

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void destroy() override;

private:
	Triangle* triangle;
};