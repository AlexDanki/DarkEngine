#pragma once
#include "../graphics/Shader.h"

class Triangle {
public:
	Triangle(Shader* shader);
	~Triangle();

	void startTriangle();
	void draw();

private:
	unsigned int VAO, VBO, EBO;
	Shader* m_shader;
};
