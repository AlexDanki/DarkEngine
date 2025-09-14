#pragma once
#include "bullet/btBulletCollisionCommon.h"
#include <vector>
#include "glm/glm.hpp" 
#include "glm/gtc/type_ptr.hpp" 
#include <iostream>

class BulletDebugDrawer : public btIDebugDraw {
private:
    int m_debugMode;
    std::vector<float> lineVertices; // x, y, z, r, g, b por vértice
    unsigned int vao, vbo;
    unsigned int shaderProgram;

public:
    BulletDebugDrawer(unsigned int shader);

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override {
        lineVertices.insert(lineVertices.end(), {
            from.getX(), from.getY(), from.getZ(), color.getX(), color.getY(), color.getZ(),
            to.getX(),   to.getY(),   to.getZ(),   color.getX(), color.getY(), color.getZ()
            });
    }

    void flushLines(const glm::mat4& view, const glm::mat4& projection);

    void setDebugMode(int debugMode) override {
        m_debugMode = debugMode;
    }

    int getDebugMode() const override {
        return m_debugMode;
    }

    void drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB,
        btScalar distance, int lifeTime, const btVector3& color) override {
        // Opcional: desenhar uma pequena linha para o ponto de contato
        btVector3 to = pointOnB + normalOnB * distance;
        drawLine(pointOnB, to, color);
    }

    void reportErrorWarning(const char* warningString) override {
        std::cerr << "Bullet Warning: " << warningString << std::endl;
    }

    void draw3dText(const btVector3& location, const char* textString) override {
        // Ignorado por enquanto
    }
};