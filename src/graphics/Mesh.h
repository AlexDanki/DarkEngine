#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../core/Transform.h"

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;

};

namespace graph {
	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};
};


class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<graph::Texture> textures);

	// Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<graph::Texture> textures;

	void draw(class Shader& shader);
	void setupMesh();

private:
	unsigned int VAO, VBO, EBO;
	

};