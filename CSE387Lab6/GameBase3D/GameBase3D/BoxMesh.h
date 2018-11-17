#pragma once
#include "Mesh.h"
class BoxMesh :
	public Mesh
{
public:
public:
	BoxMesh(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	bool Load(const std::string & fileName, Material material = Material());

protected:

	float halfWidth, halfHeight, halfDepth;
};

