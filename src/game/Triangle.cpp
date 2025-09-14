#include "glad/glad.h"
#include "Triangle.h"
#include "../graphics/Shader.h"
#include <iostream>
#include "glfw/glfw3.h"
#include "../graphics/Texture.h"

float colors[] = {
     0.0f,  0.5f, 0.0f,   // topo
    -0.5f, -0.5f, 0.0f,   // canto inferior esquerdo
     0.5f, -0.5f, 0.0f    // canto inferior direito
};

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {
       0, 1, 3, // first triangle
       1, 2, 3  // second triangle
};

Triangle::Triangle(Shader* shader)
    :VAO(0),
    VBO(0),
    EBO(0),
    m_shader(shader)
{
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::startTriangle()
{
    // Gera VAO e VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Liga VAO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define layout: localização 0 → vec3 posição
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Limpa binding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_shader->use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(m_shader->ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(m_shader->ID, "texture2"), 1);
}

void Triangle::draw()
{
    m_shader->use();

    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    //glUniform4f(glGetUniformLocation(shader.ID, "colorUni"), 0.0f, greenValue, 0.0f, 1.0f);

    Texture texture("./assets/container.jpg");
    Texture texture2("./assets/awesomeface.png");

    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    glActiveTexture(GL_TEXTURE1);
    texture2.bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    texture.unbind();
    texture2.unbind();
}
