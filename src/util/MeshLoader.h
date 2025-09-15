#pragma once
#include <vector>
#include "string"
#include "bullet/btBulletCollisionCommon.h"

struct MeshLoader {
	void loadVertices(const std::string& meshPath, std::vector<btVector3>& bulletVertices );
	btConvexHullShape* createShape(std::vector<btVector3> _bulletVertices);
};