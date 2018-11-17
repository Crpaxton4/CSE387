#include "GameBoardMesh.h"



GameBoardMesh::GameBoardMesh( GLfloat w )
	: sideLength( w ), normalVector( vec3( 0.0f, 1.0f, 0.0f ) )
{
	divisionsPerSide = (int)sideLength;

	if( divisionsPerSide % 2 != 0 ) {
		divisionsPerSide = divisionsPerSide + 1;
	}
	tileWidth = sideLength / divisionsPerSide;
}


bool GameBoardMesh::Load( const std::string & fileName, Material darkMat, Material lightMat )
{
	darkMaterial = darkMat;
	lightMaterial = lightMat;

	initilizeDarkSquares( );

	initilizeLightSquares( );

	return true;

}

void GameBoardMesh::initilizeDarkSquares( )
{
	pntVertexData v0, v1, v2, v3;


	std::vector<pntVertexData> v;
	std::vector<unsigned int> indices;

	// Find corner of the board
	GLfloat tileX = -( ( divisionsPerSide / 2.0f )  * tileWidth );
	GLfloat tileZ = ( ( divisionsPerSide / 2.0f ) * tileWidth );

	GLuint currentIndex = 0;

	// Loop through rows
	for( int j = 0; j < divisionsPerSide; j++ ) {

		// Loop through columns
		for( int i = 0; i < divisionsPerSide / 2; i++ ) {

			v0 = pntVertexData( vec3( tileX, 0.0f, tileZ - tileWidth ), normalVector, vec2(0.0f, 1.0f) );
			v.push_back( v0 );
			v1 = pntVertexData( vec3( tileX, 0.0f, tileZ ), normalVector, vec2( 0.0f, 0.0f ) );
			v.push_back( v1 );

			tileX += tileWidth;

			v2 = pntVertexData( vec3( tileX, 0.0f, tileZ ), normalVector, vec2( 1.0f, 0.0f ) );
			v.push_back( v2 );
			v3 = pntVertexData( vec3( tileX, 0.0f, tileZ - tileWidth ), normalVector, vec2( 1.0f, 1.0f ) );
			v.push_back( v3 );

			indices.push_back( currentIndex );
			indices.push_back( currentIndex + 1 );
			indices.push_back( currentIndex + 2 );

			indices.push_back( currentIndex );
			indices.push_back( currentIndex + 2 );
			indices.push_back( currentIndex + 3 );

			currentIndex += 4;

			tileX += tileWidth;

		} // end for i

		if( j % 2 == 0 ) {
			tileX = -( ( divisionsPerSide / 2.0f ) * tileWidth ) + tileWidth;
		}
		else {
			tileX = -( ( divisionsPerSide / 2.0f ) * tileWidth );
		}

		tileZ -= tileWidth;

	} // end for j

		// Create a vertex array object
	VertexArray * va = new VertexArray( v, indices );

	// Add the vertex array object to the list Mesh super class
	mVertexArrays.push_back( va );

	// Set the material for the vertex array object
	va->vaoMaterial = darkMaterial;


	v.clear( );
	indices.clear( );

} // end initilizeDarkSquares


void GameBoardMesh::initilizeLightSquares( )
{
	pntVertexData v0, v1, v2, v3;

	std::vector<pntVertexData> v;
	std::vector<unsigned int> indices;

	// Find corner of the board
	GLfloat tileX = -( ( divisionsPerSide / 2.0f )  * tileWidth ) + tileWidth;
	GLfloat tileZ = ( ( divisionsPerSide / 2.0f ) * tileWidth );

	GLuint currentIndex = 0;

	// Loop through rows
	for( int j = 0; j < divisionsPerSide; j++ ) {

		// Loop through columns
		for( int i = 0; i < divisionsPerSide / 2; i++ ) {

			v0 = pntVertexData( vec3( tileX, 0.0f, tileZ - tileWidth ), normalVector, vec2( 0.0f, 1.0f ) );
			v.push_back( v0 );
			v1 = pntVertexData( vec3( tileX, 0.0f, tileZ ), normalVector, vec2( 0.0f, 0.0f ) );
			v.push_back( v1 );

			tileX += tileWidth;

			v2 = pntVertexData( vec3( tileX, 0.0f, tileZ ), normalVector, vec2( 1.0f, 0.0f ) );
			v.push_back( v2 );
			v3 = pntVertexData( vec3( tileX, 0.0f, tileZ - tileWidth ), normalVector, vec2( 1.0f, 1.0f ) );
			v.push_back( v3 );

			indices.push_back( currentIndex );
			indices.push_back( currentIndex + 1 );
			indices.push_back( currentIndex + 2 );

			indices.push_back( currentIndex );
			indices.push_back( currentIndex + 2 );
			indices.push_back( currentIndex + 3 );

			currentIndex += 4;

			tileX += tileWidth;

		} // end for i

		if( j % 2 == 0 ) {
			tileX = -( ( divisionsPerSide / 2.0f ) * tileWidth );
		}
		else {
			tileX = -( ( divisionsPerSide / 2.0f ) * tileWidth ) + tileWidth;
		}

		tileZ -= tileWidth;

	} // end for j


		// Create a vertex array object
	VertexArray * va = new VertexArray( v, indices );

	// Add the vertex array object to the list Mesh super class
	mVertexArrays.push_back( va );

	// Set the material for the vertex array object
	va->vaoMaterial = lightMaterial;

	v.clear( );
	indices.clear( );

} // end initilizeLightSquares




