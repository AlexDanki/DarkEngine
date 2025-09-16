#include "Entity.h"
#include "../graphics/Model.h"
#include "../graphics/Shader.h"

Entity::Entity(Shader* shader, Entity* _parent) :
	transform(nullptr),
	model(nullptr),
	m_shader(shader),
	m_state(E_ACTIVE),
	parent(nullptr)
{
	addComponent<Transform>();
	transform = getComponent<Transform>();
	transform->setScale(glm::vec3(1.0, 1.0, 1.0));
	transform->setRotation(glm::vec3(0.0, 0.0, 0.0));
	setParent(_parent);
}

void Entity::setParent(Entity* newParent)
{
	if (parent == newParent) return;

	// Old parent remove Child
	if(parent)
	parent->removeChild(this);

	// Adicioandno novo parent
	parent = newParent;

	if(parent)
	// Adicionando this como filho do novo parent
	newParent->addChild(this);

}

Entity* Entity::getParent() const
{
	return parent;
}

void Entity::addChild(Entity* child)
{
	if(std::find(childrens.begin(), childrens.end(), child) == childrens.end())
	{
		childrens.push_back(child);
		child -> parent = this;
	}
}

void Entity::removeChild(Entity* child)
{
	auto children = std::find(childrens.begin(), childrens.end(), child);
	if(children != childrens.end())
	{
		(*children)->parent = nullptr;
		childrens.erase(children);
	}
}

void Entity::draw()
{
	if (m_state == E_DISABLED) return;
	if (model && m_shader) {
		//auto trans = getComponent<Transform>();
		m_shader->setMat4("model", transform->getGlobalMatrix());
		model->Draw(*m_shader);
	}
}

void Entity::start()
{
	for (auto& pair : components)
	{
		pair.second->start();
	}
}

void Entity::update(double deltaTime)
{
	if (m_state == E_DISABLED) return;

	if (m_state == E_ACTIVE)
	{
		for(auto& pair : components)
		{
			pair.second->update(deltaTime);
		}
	}
	
}
