#include "ModelMesh.h"
#include "Renderer.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL_log.h>
#include "MathLibsConstsFuncs.h"
#include <iostream>


bool ModelMesh::Load( class Renderer* renderer, const std::string & filename )
{

	// Model loading
	std::vector<pntVertexData> vData;
	std::vector<unsigned int> indices;

	// Create an instance of the Importer class
	Assimp::Importer importer;

	// Load the scene/model and associated meshes into a aiScene object
	// See http://www.assimp.org/lib_html/class_assimp_1_1_importer.html#afa338a135a56956bd5deb7d238498dde 
	// for more details. Second argument specifies configuration that is optimized for 
	// real-time rendering.
	const aiScene *scene = importer.ReadFile( filename, aiProcessPreset_TargetRealtime_Quality );

	// Check if the scene/model loaded correctly
	if( !scene ) {
		std::cerr << "ERROR: Unable to load " << filename <<
			std::endl << "\t" << importer.GetErrorString( ) << std::endl;
		return false;
	}
	else {
		std::cout << "Loading Model: " << filename << std::endl;
	}


	/*
	This is a concave shape made out of convex sub parts, called child shapes. Each
	child shape has its own local offset transform, relative to the btCompoundShape. It is a good idea to
	approximate concave shapes using a collection of convex hulls, and store them in a
	btCompoundShape.
	*/
	// Create compound shape to hold the shapes of the indivicdual meshes
	btCompoundShape * modelCompondShape = new btCompoundShape( );

	// Iterate through each mesh
	for( size_t i = 0; i < scene->mNumMeshes; i++ ) {

		// Get the vertex mesh 
		aiMesh *mesh = scene->mMeshes[i];

		btConvexHullShape * meshCollisionShape = new btConvexHullShape();

		ReadVertexData( mesh, vData, indices, *meshCollisionShape );

		// Get the material for the mesh
		aiMaterial* meshMaterial = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];

		Material material;

		// Read in the material properties for this mesh
		if( mesh->mMaterialIndex >= 0 ) {

			material = readInMaterialProperties( renderer, meshMaterial, filename );

		}

		//std::cout << "Number of vertices: " << vData.size( ) << std::endl;

		VertexArray * va = new VertexArray( vData, indices ); // Is his a memory leak?
		va->vaoMaterial = material;

		// Push back the VAO and the textureID associated with it.
		mVertexArrays.push_back( va );

		// Add the mesh collision shape for collision detection
		// Do NOT use the default btTransform constructor for this! It apparently makes a zero matrix.
		// No problem for collision spheres! 
		modelCompondShape->addChildShape( btTransform( btQuaternion( 0, 0, 0 ) ), meshCollisionShape ); // Is this collision shape going to disapear??

		vData.clear( );
		indices.clear( );
	}

	// Save the compond collision shape for this model
	this->collisionShape = modelCompondShape;

	return true;
}


void ModelMesh::ReadVertexData( aiMesh *mesh, std::vector<pntVertexData> &vertexData, std::vector<unsigned int> &indices, btConvexHullShape & hull )
{
	// Read in vertex positions, normals, and texture coordinates. See 
	// http://www.assimp.org/lib_html/structai_mesh.html for more details
	if( mesh->HasPositions( ) ) {
		for( unsigned int i = 0; i < mesh->mNumVertices; ++i ) {
			glm::vec3 tempPosition;
			tempPosition.x = mesh->mVertices[i].x;
			tempPosition.y = mesh->mVertices[i].y;
			tempPosition.z = mesh->mVertices[i].z;

			hull.addPoint( btVector3( tempPosition.x, tempPosition.y, tempPosition.z ), true );

			glm::vec3 tempNormal;

			tempNormal.x = mesh->mNormals[i].x;
			tempNormal.y = mesh->mNormals[i].y;
			tempNormal.z = mesh->mNormals[i].z;

			//glm::vec3 tempTangent;
			//glm::vec3 tempbitTangent;

			//if( mesh->HasTangentsAndBitangents( ) ) {

			//	tempTangent.x = mesh->mTangents[i].x;
			//	tempTangent.y = mesh->mTangents[i].y;
			//	tempTangent.z = mesh->mTangents[i].z;

			//	tempbitTangent.x = mesh->mBitangents[i].x;
			//	tempbitTangent.y = mesh->mBitangents[i].y;
			//	tempbitTangent.z = mesh->mBitangents[i].z;
			//}

			glm::vec2 tempCoord( 0.0f, 0.0f );

			// Should always be true since coordinates are auto generated if not present
			if( mesh->HasTextureCoords( 0 ) ) {
				tempCoord.x = mesh->mTextureCoords[0][i].x;
				tempCoord.y = mesh->mTextureCoords[0][i].y;
			}

			vertexData.push_back( pntVertexData( tempPosition, tempNormal, tempCoord ) );
		}
	}

	// Read out the indices and buffer them
	if( mesh->HasFaces( ) ) {
		for( unsigned int i = 0; i < mesh->mNumFaces; ++i ) {
			indices.push_back( mesh->mFaces[i].mIndices[0] );
			indices.push_back( mesh->mFaces[i].mIndices[1] );
			indices.push_back( mesh->mFaces[i].mIndices[2] );
		}
	}

} // bufferVertexData


std::string ModelMesh::GetDirectoryPath( std::string sFilePath )
{
	// Get directory path
	std::string sDirectory = "";

	for( int i = (int)sFilePath.size( ) - 1; i >= 0; i-- ) {

		if( sFilePath[i] == '\\' || sFilePath[i] == '/' ) {
			sDirectory = sFilePath.substr( 0, i + 1 );
			break;
		}
	}
	return sDirectory;
}


Material ModelMesh::readInMaterialProperties( Renderer* renderer, aiMaterial* assimpMaterial, std::string filename )
{
	Material meshMaterial;

	// Read in the name of the material
	aiString name;
	assimpMaterial->Get( AI_MATKEY_NAME, name );
	std::cout << "Loading " << name.C_Str( ) << " material:" << std::endl;

	// Default Material Color
	aiColor3D matColor( 0.0f, 0.0f, 0.0f );

	// Process materials (See http://www.assimp.org/lib_html/materials.html for details)

	// Query for ambient color
	if( assimpMaterial->Get( AI_MATKEY_COLOR_AMBIENT, matColor ) == AI_SUCCESS ) {

		meshMaterial.setAmbientMat( glm::vec4( matColor[0], matColor[1], matColor[2], 1.0 ) );
	}
	// Query for diffuse color
	if( assimpMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, matColor ) == AI_SUCCESS ) {

		meshMaterial.setDiffuseMat( glm::vec4( matColor[0], matColor[1], matColor[2], 1.0 ) );
	}
	// Query for specular color
	if( assimpMaterial->Get( AI_MATKEY_COLOR_SPECULAR, matColor ) == AI_SUCCESS ) {

		meshMaterial.setSpecularMat( glm::vec4( matColor[0], matColor[1], matColor[2], 1.0 ) );
	}
	// Query for emissive color
	if( assimpMaterial->Get( AI_MATKEY_COLOR_EMISSIVE, matColor ) == AI_SUCCESS ) {

		meshMaterial.setEmissiveMat( glm::vec4( matColor[0], matColor[1], matColor[2], 1.0 ) );
	}

	// Path to the texture
	aiString path;

	// Load diffuse, specular, and normal maps
	if( assimpMaterial->GetTextureCount( aiTextureType_DIFFUSE ) > 0 ) {

		if( AI_SUCCESS == assimpMaterial->GetTexture( aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr ) ) {

			std::string relativeFilePath = GetDirectoryPath( filename ) + path.C_Str( );
			std::cout << "Loading texture: " << relativeFilePath << std::endl;

			meshMaterial.setDiffuseTexture( renderer->GetTexture( relativeFilePath )->GetTextureObject( ) );
		}
	}
	if( assimpMaterial->GetTextureCount( aiTextureType_SPECULAR ) > 0 ) {

		if( AI_SUCCESS == assimpMaterial->GetTexture( aiTextureType_SPECULAR, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr ) ) {

			std::string relativeFilePath = GetDirectoryPath( filename ) + path.C_Str( );
			std::cout << "Loading texture: " << relativeFilePath << std::endl;

			meshMaterial.setSpecularTexture( renderer->GetTexture( relativeFilePath )->GetTextureObject( ) );
		}
	}
	if( assimpMaterial->GetTextureCount( aiTextureType_NORMALS ) > 0 ) {

		if( AI_SUCCESS == assimpMaterial->GetTexture( aiTextureType_NORMALS, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr ) ) {

			std::string relativeFilePath = GetDirectoryPath( filename ) + path.C_Str( );
			std::cout << "Loading texture: " << relativeFilePath << std::endl;

			meshMaterial.setNormalMap( renderer->GetTexture( relativeFilePath )->GetTextureObject( ) );
		}
	}

	return meshMaterial;

} // end readInMaterialProperties
