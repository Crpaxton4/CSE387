#pragma once
#include "Mesh.h"

class SphereMesh :
	public Mesh
{
	public:
	SphereMesh( GLfloat radius = 2.0f, GLint stacks = 8, GLint slices = 16 );

	bool Load( const std::string & fileName, Material material = Material( ) );

	protected:

	void initializeTop( );
	void initializeBody( );
	void initializeBottom( );

	GLint stacks;
	GLint slices;
	GLfloat radius;

	std::vector<GLfloat> stackAngles;
	std::vector<GLfloat> sliceAngles;

	std::vector<pntVertexData> v;
	std::vector<unsigned int> indices;

	unsigned int indiceCounter = 0;

};

