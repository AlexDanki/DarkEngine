#pragma once
#include <vector>
#include "string"
#include "bullet/btBulletCollisionCommon.h"
#include "assimp/Importer.hpp"

struct MeshLoader {
public:

	void loadVertices(const std::string& meshPath, std::vector<btVector3>& bulletVertices );
	btConvexHullShape* createShape(std::vector<btVector3> _bulletVertices);
	void loadTriangles(const std::string& meshPath, btTriangleMesh* triMesh,const aiScene* loadedScene);
	btBvhTriangleMeshShape* createTerrainShape(btTriangleMesh* triMesh);
};