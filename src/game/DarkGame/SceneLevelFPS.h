#pragma once
#include "../../core/Scene.h"
#include "../Triangle.h"
#include "../../core/Engine.h"

class SceneLevelFPS : public Scene {
public:
	SceneLevelFPS(Engine* engine): Scene(engine),triangle(nullptr) {};

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void destroy() override;
	void loadData() override;

private:
	Triangle* triangle;

	class Model* guyModel;
	class Model* camModel;
	class Model* shotgunModel;
	class Model* groundModel;
	class Model* bunkerModel;
};