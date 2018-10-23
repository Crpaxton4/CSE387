// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Mesh.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL_log.h>
#include "MathLibsConstsFuncs.h"

Mesh::Mesh()
	:mVertexArray(nullptr)
	,mRadius(0.0f)
{
}

Mesh::~Mesh()
{
}

bool Mesh::Load(class Renderer* renderer, const std::string & fileName )
{

	std::vector<pntVertexData> vData;
	std::vector<unsigned int> indices;

	if( fileName == "" ) {

		// Load the default mesh
		//TODO




	}
	else {

		// TODO 
		// Model loading

	}

	mVertexArray = new VertexArray( vData, indices );

	vData.clear( );
	indices.clear( );

	return true;
}

void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}


