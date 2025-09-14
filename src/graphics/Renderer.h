#pragma once
#include <vector>
#include <map>
#include "../physics/BulletDebugDrawer.h"
#include <glm/mat4x4.hpp>


class Renderer {
public:
	Renderer();

	void init(); // Inicializa o renderer (GLAD, configurações iniciais)

	void beginFrame(); // Inicia o frame (limpa a tela)

	void setClearScreen(float _r, float _g, float _b, float _a); // Define a cor de fundo

	void drawEntityes(std::map<class Shader*, std::vector<class Entity*>> renderGroups); // Função de desenho - Implementar se necessário

	void UpdateCameraView(class Camera* camera, class Shader* shader);

	void drawSkybox(class Shader* skyShader, class Skybox* skybox, class Camera* camera, unsigned int textureId);

	void drawCollisors(class Camera* camera);

	BulletDebugDrawer* getDebugDrawer() { return debugDrawer; }

	glm::mat4 projMatrix();

private:
	float r, g, b, a; // Cor de fundo
	class GLFWwindow* m_window;
	BulletDebugDrawer* debugDrawer;
};