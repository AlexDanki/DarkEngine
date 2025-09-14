#pragma once

class Component {
public:
	class Entity* m_owner = nullptr;
	virtual ~Component() = default;
	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	
};