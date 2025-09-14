#include "DefaultScene.h"
#include "../graphics/Shader.h"
#include <iostream>
#include "../graphics/Renderer.h"



void DefaultScene::init()
{
	std::cout << "Iniciou defaultScene \n";
	//triangle = new Triangle(shader);
	//triangle->startTriangle();
}

void DefaultScene::update(float deltaTime)
{
	std::cout << "Rodando defaultScene \n";
}

void DefaultScene::render()
{

	//triangle->draw();
}

void DefaultScene::destroy()
{
	//delete triangle;
}

