#include "Renderer.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <iostream>
#include "../core/Entity.h"
#include "../graphics/Shader.h" 
#include "./Camera.h"
#include "./Skybox.h"
#include <vector>
#include <string>


Renderer::Renderer():
	debugDrawer(nullptr)
{
}

void Renderer::init()
{
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);        // Ativa o culling
	glCullFace(GL_BACK);           // Cula as faces traseiras
	glFrontFace(GL_CCW);           // Define que vértices CCW são frente (padrão do Blender)

	Shader* bullet_debug = new Shader("./shaders/bullet_debug.vert", "./shaders/bullet_debug.frag");
	debugDrawer = new BulletDebugDrawer(bullet_debug->ID);
	
}

void Renderer::beginFrame()
{
	glClearColor(r, g, b, a); // Cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearScreen(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

void Renderer::drawEntityes(std::map<Shader*, std::vector<Entity*>> renderGroups)
{
	for (auto& pair : renderGroups) {
		Shader* shader = pair.first;

		for (Entity* e : pair.second) {
			if (e->m_state == E_ACTIVE)
			{
				shader->use();
				e->draw();
			}
		}
	}
}

void Renderer::UpdateCameraView(Camera* camera, Shader* shader)
{
	shader->use();
	shader->setMat4("view", camera->getViewMatrix());
	shader->setMat4("proj", projMatrix());
}

void Renderer::drawSkybox(Shader* skyShader, Skybox* skybox, Camera* camera, unsigned int textureId)
{
	
	glDepthFunc(GL_LEQUAL); // permite que a skybox passe no teste de profundidade
	//glDepthMask(GL_FALSE);

	skyShader->use();

	// ?? Primeiro: atualiza as matrizes
	glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));
	skyShader->setMat4("view", view);
	skyShader->setMat4("projection", projMatrix());
	skyShader->setInt("skybox", 0); // se estiver usando GL_TEXTURE0

	// ?? Depois: desenha a skybox
	glBindVertexArray(skybox->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//glDepthMask(GL_TRUE);   // reativa escrita
	glDepthFunc(GL_LESS);   // volta ao padrão
}

glm::mat4 Renderer::projMatrix()
{
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 900.0f / 600.0f, 0.1f, 100.0f);
	return projection;
}

void Renderer::drawCollisors(Camera* camera)
{
	debugDrawer->flushLines(camera->getViewMatrix(), projMatrix());
}





