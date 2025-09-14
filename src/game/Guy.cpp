#include "Guy.h"
#include <glfw/glfw3.h>

float angle = 0;

Guy::Guy(Shader* shader) : Entity(shader)
{
}

void Guy::start()
{
	Entity::start();
}

void Guy::update(double deltaTime)
{
	Entity::update(deltaTime);
}
