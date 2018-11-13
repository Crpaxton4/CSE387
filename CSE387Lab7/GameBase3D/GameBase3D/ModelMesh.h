#pragma once
#include "Mesh.h"

// Includes for model loading
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"


class ModelMesh :
	public Mesh
{
	public:

	// Load/unload mesh
	bool Load( class Renderer* renderer, const std::string & fileName = "" );

	protected:

	void ReadVertexData( aiMesh * mesh, std::vector<pntVertexData>& vertexData, std::vector<unsigned int>& indices );
	std::string GetDirectoryPath( std::string sFilePath );

	Material readInMaterialProperties( Renderer* renderer, aiMaterial* assimpMaterial, std::string filename );

};

