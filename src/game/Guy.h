#pragma once
#include "../core/Entity.h"

class Guy : public Entity
{
public:
	Guy(class Shader* shader = nullptr, Entity* _parent = nullptr);
	void start() override;
	void update(float deltaTime) override;
};