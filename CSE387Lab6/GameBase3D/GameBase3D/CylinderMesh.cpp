#include "CylinderMesh.h"

vec2 getCylindericalTextCoords( float theta, vec3 vertex, float height )
{
	float s = theta / ( 2.0f * PI );

	float t = vertex.z / height;

	return vec2( s, t );
}

CylinderMesh::CylinderMesh( float height, float radius, int stacks, int slices )
	:stacks( stacks ), slices( slices ), height( height ), radius( radius )
{
}


bool CylinderMesh::Load( const std::string & fileName, Material material  )
{
	initializeCylinderBottom( material );
	initializeCylinderBody( material );
	initializeCylinderTop( material );

	return true;
}

void CylinderMesh::initializeCylinderBody( Material material )
{
	// Step in z and radius as stacks are drawn.
	double z0, z1;
	const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
	float angleStep = 2.0f * PI / slices;

	// vector containers to hold  data
	std::vector<pntVertexData> v; // vertex positions
	std::vector<unsigned int> indices; // indices

	// Do the stacks */
	z0 = 0.0;
	z1 = zStep;
	GLuint currentIndex = 0;

	float theta = 0.0f;

	for( int i = 1; i <= stacks; i++ ) {
		if( i == stacks ) {
			z1 = height;
		}

		for( int j = 0; j < slices; j++ ) {

			theta = j * angleStep;

			vec3 n01 = vec3( cos( theta ), sin( theta ), 0.0 );
			vec3 v0 = vec3( cos( theta )*radius, sin( theta )*radius, z0 );
			v.push_back( pntVertexData( v0, n01, getCylindericalTextCoords( theta, v0, height ) ) ); // 0

			vec3 v1 = vec3( cos( theta )*radius, sin( theta )*radius, z1 );
			v.push_back( pntVertexData( v1, n01, getCylindericalTextCoords( theta, v1, height ) ) ); // 1

			theta = ( j + 1 )* angleStep;
			vec3 n23 = vec3( cos( theta ), sin( theta ), 0.0 );

			vec3 v2 = vec3( cos( theta )*radius, sin( theta )*radius, z0 );
			v.push_back( pntVertexData( v2, n23, getCylindericalTextCoords( theta, v2, height ) ) ); // 2

			vec3 v3 = vec3( cos( theta )*radius, sin( theta )*radius, z1 );
			v.push_back( pntVertexData( v3, n23, getCylindericalTextCoords( theta, v3, height ) ) ); // 3

			indices.push_back( currentIndex );
			indices.push_back( currentIndex + 2 );
			indices.push_back( currentIndex + 3 );

			indices.push_back( currentIndex );
			indices.push_back( currentIndex + 3 );
			indices.push_back( currentIndex + 1 );

			currentIndex += 4;
		}

		z0 = z1;
		z1 += zStep;
	}

	// Create a vertex array object
	VertexArray * va = new VertexArray( v, indices );

	// Add the vertex array object to the list Mesh super class
	mVertexArrays.push_back( va );

	// Set the material for the vertex array object
	va->vaoMaterial = material;

	v.clear( );
	indices.clear( );

} // end initializeCylinderBody

void CylinderMesh::initializeCylinderBottom( Material material )
{
	float angleStep = 2.0f * PI / slices;

	// vector containers to hold  data
	std::vector<pntVertexData> v; // vertex positions
	std::vector<unsigned int> indices; // indices

	GLuint currentIndex = 0;

	vec3 normal = vec3( 0.0, 0.0, -1.0 );
	vec3 bottomCtr = vec3( 0.0, 0.0, 0.0 );

	float theta = 0.0f;
	for( int j = slices; j >= 0; j-- ) {

		theta = j * angleStep;
		vec3 v0 = vec3( cos( theta ) * radius, sin( theta )*radius, 0.0f );
		v.push_back( pntVertexData( v0, normal, getCylindericalTextCoords( theta, v0, height ) ) );
		indices.push_back( currentIndex++ );

		theta = ( j - 1 ) * angleStep;
		v0 = vec3( cos( theta ) * radius, sin( theta )*radius, 0.0f );
		v.push_back( pntVertexData( v0, normal, getCylindericalTextCoords( theta, v0, height ) ) );
		indices.push_back( currentIndex++ );

		theta = j * angleStep - angleStep / 2;
		v.push_back( pntVertexData( bottomCtr, normal, getCylindericalTextCoords( theta, bottomCtr, height ) ) );
		indices.push_back( currentIndex++ );

	}

	// Create a vertex array object
	VertexArray * va = new VertexArray( v, indices );

	// Add the vertex array object to the list Mesh super class
	mVertexArrays.push_back( va );

	// Set the material for the vertex array object
	va->vaoMaterial = material;

	v.clear( );
	indices.clear( );

} // end initializeCylinderBottom

void CylinderMesh::initializeCylinderTop( Material material )
{
	float angleStep = 2.0f * PI / slices;

	// vector containers to hold  data
	std::vector<pntVertexData> v; // vertex positions
	std::vector<unsigned int> indices; // indices

	GLuint currentIndex = 0;

	vec3 normal = vec3( 0.0, 0.0, 1.0 );
	vec3 topCtr = vec3( 0.0, 0.0, height );

	float theta = 0.0f;

	for( int j = 0; j <= slices; j++ ) {

		theta = j * angleStep;
		vec3 v0 = vec3( cos( theta ) * radius, sin( theta )*radius, height );
		v.push_back( pntVertexData( v0, normal, getCylindericalTextCoords( theta, v0, height ) ) );
		indices.push_back( currentIndex++ );

		theta = ( j + 1 ) * angleStep;
		v0 = vec3( cos( theta ) * radius, sin( theta )*radius, height );
		v.push_back( pntVertexData( v0, normal, getCylindericalTextCoords( theta, v0, height ) ) );
		indices.push_back( currentIndex++ );

		theta = (j)* angleStep + angleStep / 2;
		v.push_back( pntVertexData( topCtr, normal, getCylindericalTextCoords( theta, topCtr, height ) ) );
		indices.push_back( currentIndex++ );
	}

	// Create a vertex array object
	VertexArray * va = new VertexArray( v, indices );

	// Add the vertex array object to the list Mesh super class
	mVertexArrays.push_back( va );

	// Set the material for the vertex array object
	va->vaoMaterial = material;

	v.clear( );
	indices.clear( );

} // end initializeCylinderTop
