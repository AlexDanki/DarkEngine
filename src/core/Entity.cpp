#include "Entity.h"
#include "../graphics/Model.h"
#include "../graphics/Shader.h"

Entity::Entity(Shader* shader) :
	transform(nullptr),
	model(nullptr),
	m_shader(shader),
	m_state(E_ACTIVE)
{
	addComponent<Transform>();
	transform = getComponent<Transform>();
	transform->setScale(glm::vec3(1.0, 1.0, 1.0));
	transform->setRotation(glm::vec3(0.0, 0.0, 0.0));
}

void Entity::draw()
{
	if (m_state == E_DISABLED) return;
	if (model && m_shader) {
		//auto trans = getComponent<Transform>();
		m_shader->setMat4("model", transform->modelMatrix());
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
