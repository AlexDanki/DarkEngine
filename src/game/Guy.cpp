#include "Guy.h"
#include <glfw/glfw3.h>

float angle = 0;

Guy::Guy(Shader* shader, Entity* _parent) : Entity(shader, _parent)
{
}

void Guy::start()
{
	Entity::start();
}

void Guy::update(float deltaTime)
{
	Entity::update(deltaTime);
}
