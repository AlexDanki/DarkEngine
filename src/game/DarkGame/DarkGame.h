#pragma once
#include "../../game/Game.h"


class DarkGame : public Engine{
public:
	void run();

	void init();
	void processInput() override;
	void update() override;
	void render() override;
	void draw() override;
	void start() override;
	void shutdown() override;
};