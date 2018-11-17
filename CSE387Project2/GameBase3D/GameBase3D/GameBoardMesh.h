#pragma once
#include "Mesh.h"
class GameBoardMesh : public Mesh
{
	public:
	GameBoardMesh( GLfloat w = 8.0f );

	bool Load( const std::string & fileName, Material darkMat, Material lightMat  );

	protected:

	void initilizeDarkSquares( );
	void initilizeLightSquares( );

	int darkSquareIndices;
	int lightSquareIndices;

	GLfloat sideLength;
	int divisionsPerSide;
	GLfloat tileWidth;

	Material darkMaterial;
	Material lightMaterial;

	const vec3 normalVector;


};

