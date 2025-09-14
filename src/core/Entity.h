#pragma once
#include "../core/Transform.h"
#include <unordered_map>
#include <typeindex>
#include "./Component.h"
#include <memory>
#include <iostream>
#include <string>

enum E_State {
	E_ACTIVE,
	E_DISABLED,
	E_DEAD
};

class Entity {
public:
	Entity(class Shader* shader = nullptr);
	std::string name = "Entity";
	class Model* model;
	std::shared_ptr<Transform> transform;
	E_State m_state;

	void setName(std::string _name) { name = _name; }
	void setModel(class Model* m) { model = m; }
	//void setTransform(class Transform* t) { transform = t; }

	template<typename T, typename... Args>
	void addComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from component");
		components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
		components[typeid(T)]->m_owner = this;
	}

	template<typename T>
	std::shared_ptr<T> getComponent()
	{
		auto it = components.find(typeid(T));
		if(it != components.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	template<typename T>
	bool hasComponent() const {
		return components.find(typeid(T)) != components.end();
	}

	template<typename T>
	void removeComponent()
	{
		components.erase(typeid(T));
	}

	
	virtual void start();
	virtual void update(double deltaTime);
	void draw();
	class Shader* getShader() { return m_shader; }

	bool hasAShader() { return m_shader != nullptr; }

private:
	class Shader* m_shader;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> components;

};