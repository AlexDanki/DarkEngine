#include "MeshLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <iostream>


void MeshLoader::loadVertices(const std::string& meshPath, std::vector<btVector3>& bulletVertices)
{
	Assimp::Importer importer;
	
	// Carrega o modelo com algumas etapas de pos processamento
	const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices );

	// Verifica se o modelo foi carregado com sucesso
	if(!scene || !scene->HasMeshes())
	{
		std::cerr << "Erro ao carregar modelo " << importer.GetErrorString() << "\n";
		return;
	}

	// itera sobre todos os meshes da cena
	for(unsigned int m = 0; m < scene->mNumMeshes; m++)
	{
		const aiMesh* mesh = scene->mMeshes[0];
		// itera sobre todos os vertices da malha
		for(unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			const aiVector3D& v = mesh->mVertices[i];
			bulletVertices.emplace_back(v.x, v.y, v.z);
		}
	}

}

btConvexHullShape* MeshLoader::createShape(std::vector<btVector3> _bulletVertices)
{
	btConvexHullShape* shape = new btConvexHullShape();
	for (auto v : _bulletVertices)
	{
		shape->addPoint(v);
	}
	return shape;
}
