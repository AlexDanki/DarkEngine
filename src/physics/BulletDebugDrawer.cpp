#include "BulletDebugDrawer.h"
#include "glad/glad.h"


BulletDebugDrawer::BulletDebugDrawer(unsigned int shader) : m_debugMode(DBG_DrawWireframe), shaderProgram(shader)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
}

void BulletDebugDrawer::flushLines(const glm::mat4& view, const glm::mat4& projection)
{
    if (lineVertices.empty()) return;

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, lineVertices.size() * sizeof(GLfloat), lineVertices.data(), GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); // posição
    glEnableVertexAttribArray(1); // cor

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glDrawArrays(GL_LINES, 0, lineVertices.size() / 6);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    lineVertices.clear();
}
