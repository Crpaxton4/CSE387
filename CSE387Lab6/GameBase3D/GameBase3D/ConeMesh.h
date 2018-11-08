#pragma once
#include "Mesh.h"
class ConeMesh :
	public Mesh
{
	public:
	ConeMesh( float height = 2.0f, float base = 0.5f, int stacks = 4, int slices = 16 );

	bool Load( const std::string & fileName, Material material = Material( ) );

	protected:

	void initializeConeBody( Material material );
	void initializeConeBottom( Material material );

	int stacks, slices;
	float height, base;
};

