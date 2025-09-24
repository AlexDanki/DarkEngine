#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./Component.h"
#include <vector>

class Transform : public Component{

public:
	Transform();
	glm::vec3 curPosition;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void start() override;
	void update(float deltaTime) override;

	void setPosition(const glm::vec3& pos) { position = pos; }
	void setRotation(const glm::vec3& rot) { rotation = rot; }
	void setScale(const glm::vec3& scl) { scale = scl; }

	// Hierarquia
	glm::mat4 getLocalMatrix();
	glm::mat4 getGlobalMatrix();

	glm::vec3 getFront();
	glm::vec3 getRight();
	glm::vec3 getUp();

	glm::mat4 modelMatrix();
	glm::mat4 viewMatrix();
	glm::mat4 projMatrix();

private:
	class btRigidBody* m_ownerRb;
	bool firstTime;
};
