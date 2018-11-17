#pragma once
#include "Mesh.h"
class CylinderMesh : public Mesh
{
	public:
	CylinderMesh( float height = 2.0f, float radius = 0.5f, int stacks = 4, int slices = 16 );

	bool Load( const std::string & fileName, Material material = Material( ) );

	protected:

	void initializeCylinderBody( Material material );
	void initializeCylinderBottom( Material material );
	void initializeCylinderTop( Material material );

	int stacks, slices;
	float height, radius;

};

