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

void MeshLoader::loadTriangles(const std::string& meshPath, btTriangleMesh* triMesh)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(meshPath,
        aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);

    if (!scene || !scene->HasMeshes()) {
        std::cerr << "Erro ao carregar modelo: " << importer.GetErrorString() << "\n";
        return;
    }

    for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
        const aiMesh* mesh = scene->mMeshes[m];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];

            if (face.mNumIndices != 3) continue; // Garante que é um triângulo

            btVector3 v0 = btVector3(
                mesh->mVertices[face.mIndices[0]].x,
                mesh->mVertices[face.mIndices[0]].y,
                mesh->mVertices[face.mIndices[0]].z
            );
            btVector3 v1 = btVector3(
                mesh->mVertices[face.mIndices[1]].x,
                mesh->mVertices[face.mIndices[1]].y,
                mesh->mVertices[face.mIndices[1]].z
            );
            btVector3 v2 = btVector3(
                mesh->mVertices[face.mIndices[2]].x,
                mesh->mVertices[face.mIndices[2]].y,
                mesh->mVertices[face.mIndices[2]].z
            );

            triMesh->addTriangle(v0, v1, v2);
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

btBvhTriangleMeshShape* MeshLoader::createTerrainShape(btTriangleMesh* triMesh)
{
    return new btBvhTriangleMeshShape(triMesh, true);
}
