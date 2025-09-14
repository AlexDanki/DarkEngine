#pragma once
#include <vector>
#include <string>

class Skybox {
public:
	Skybox();
	~Skybox();

	const unsigned int getVAO() { return VAO; }
	int loadCubeMap(std::vector<std::string>& faces);
	void setupMesh();

private:
	unsigned int textureID, VAO, VBO;

	
	
};