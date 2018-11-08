#pragma once
#include "Mesh.h"
class PlaneMesh :
	public Mesh
{
public:
	PlaneMesh(float width = 1.0f, float height = 1.0f);

	bool Load(const std::string & meshNamae, Material material = Material());

protected:

	float halfWidth, halfHeight;
};

