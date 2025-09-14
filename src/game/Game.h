#pragma once
#include "../core/Engine.h"

class Game : public Engine{
public:
	Game();
	~Game();

	//void init();
	void run();
	
	void init();
	void processInput() override;
	void update() override;
	void render() override;
	void draw() override;
	void start() override;
	void shutdown() override;

private:
};