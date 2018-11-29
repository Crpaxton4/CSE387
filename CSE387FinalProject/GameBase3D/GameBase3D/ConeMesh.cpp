#include "ConeMesh.h"

vec2 getPlanarTextCoords( vec3 vertex, float width, float height )
{
	float s = vertex.x + width / 2;
	float t = vertex.z / height;

	return vec2( s, t );
}


ConeMesh::ConeMesh( float height, float base, int numMajor, int numMinor )
	:stacks( numMajor ), slices( numMinor ), height( height ), base( base )
{
}

bool ConeMesh::Load( const std::string & fileName, Material material )
{
	initializeConeBottom( material );
	initializeConeBody( material );

	// ************ Shape will not match Cone. Cone base is at Z equals 0.
	this->collisionShape = new btCylinderShapeZ( btVector3( base, height*0.5f, 0 ) );

	return true;
}


void ConeMesh::initializeConeBody( Material material )
{
	// Step in z and radius as stacks are drawn.
	double z0, z1;
	double r0, r1;

	const float angleStep = 2.0f * PI / slices;
	const float zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
	const float rStep = base / ( ( stacks > 0 ) ? stacks : 1 );

	// Scaling factors for vertex normals 
	const float cosn = ( height / sqrt( height * height + base * base ) );
	const float sinn = ( base / sqrt( height * height + base * base ) );

	// vector containers to hold  data
	std::vector<pntVertexData> v; // vertex positions
	std::vector<unsigned int> indices; // indices

	// Do the stacks
	z0 = 0.0;
	z1 = zStep;

	r0 = base;
	r1 = r0 - rStep;

	GLuint currentIndex = 0;

	float theta = 0.0f;

	for( int i = 0; i < stacks - 1; i++ ) {
		for( int j = 0; j < slices; j++ ) {
			theta = j * angleStep;

			vec3 n01 = vec3( cos( theta ) * cosn, sin( theta )*cosn, sinn );

			vec3 v0 = vec3( cos( theta ) * r0, sin( theta )*r0, z0 );
			v.push_back( pntVertexData( v0, n01, getPlanarTextCoords( v0, base, height ) ) ); // 0

			vec3 v1 = vec3( cos( theta ) * r1, sin( theta )*r1, z1 );
			v.push_back( pntVertexData( v1, n01, getPlanarTextCoords( v1, base, height ) ) ); // 1

			theta = ( j + 1 )* angleStep;
			vec3 n23 = vec3( cos( theta ) * cosn, sin( theta ) * cosn, sinn );

			vec3 v2 = vec3( cos( theta ) * r0, sin( theta ) * r0, z0 );
			v.push_back( pntVertexData( v2, n23, getPlanarTextCoords( v2, base, height ) ) ); // 2

			vec3 v3 = vec3( cos( theta ) * r1, sin( theta ) * r1, z1 );
			v.push_back( pntVertexData( v3, n23, getPlanarTextCoords( v3, base, height ) ) ); // 3

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
		r0 = r1;
		r1 -= rStep;
	}

	vec3 n = vec3( cos( 0.0 )*cosn, sin( 0.0 )*cosn, sinn );


	for( int j = 0; j < slices; j++ ) {
		theta = j * angleStep;

		vec3 v0 = vec3( cos( theta ) * r0, sin( theta ) * r0, z0 );
		v.push_back( pntVertexData( v0, n, getPlanarTextCoords( v0, base, height ) ) ); // 0

		vec3 v1 = vec3( 0, 0, height );
		v.push_back( pntVertexData( v1, n, getPlanarTextCoords( v1, base, height ) ) ); // 1

		theta = ( j + 1 )* angleStep;

		n = vec3( cos( theta ) * cosn, sin( theta ) * cosn, sinn );
		vec3 v2 = vec3( cos( theta ) * r0, sin( theta )*r0, z0 );
		v.push_back( pntVertexData( v2, n, getPlanarTextCoords( v2, base, height ) ) ); // 2

		indices.push_back( currentIndex );
		indices.push_back( currentIndex + 2 );
		indices.push_back( currentIndex + 1 );
		currentIndex += 3;
	}

	// Create a vertex array object
	VertexArray * va = new VertexArray( v, indices );

	// Add the vertex array object to the list Mesh super class
	mVertexArrays.push_back( va );

	// Set the material for the vertex array object
	va->vaoMaterial = material;


	v.clear( );
	indices.clear( );

} // end

void ConeMesh::initializeConeBottom( Material material )
{
	float angleStep = 2.0f * PI / slices;

	// vector containers to hold  data
	std::vector<pntVertexData> v; // vertex positions
	std::vector<unsigned int> indices; // indices

	GLuint currentIndex = 0;

	vec3 n = vec3( 0.0f, 0.0f, -1.0f );
	vec3 ctr = vec3( 0.0f, 0.0f, 0.0f );

	float theta = 0.0f;

	for( int j = slices; j >= 0; j-- ) {

		theta = j * angleStep;
		vec3 v0 = vec3( cos( theta ) * base, sin( theta ) * base, 0.0f );
		v.push_back( pntVertexData( v0, n, getPlanarTextCoords( v0, base, height ) ) );
		indices.push_back( currentIndex++ );

		theta = ( j - 1 )* angleStep;

		vec3 v1 = vec3( cos( theta ) * base, sin( theta ) * base, 0.0f );
		v.push_back( pntVertexData( v1, n, getPlanarTextCoords( v1, base, height ) ) );
		indices.push_back( currentIndex++ );

		v.push_back( pntVertexData( ctr, n, getPlanarTextCoords( ctr, base, height ) ) );
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

} // end initializeConeBottom
