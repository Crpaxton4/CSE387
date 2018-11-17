// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include <string>

#include "VertexArray.h"
#include "Texture.h"

// Includes for model loading
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

#include "SharedMaterialProperties.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	// Load
//	virtual bool Load( class Renderer* renderer, const std::string & fileName = "" ) { return false; };

	// Unload mesh
	void Unload();

	// Get the vertex arrays associated with this mesh
	std::vector<VertexArray*> GetVertexArrays() { return mVertexArrays; }

	// Get object space bounding sphere radius
	float GetRadius() const { return mRadius; }

	int numberOfVertexArrayObjects() const { return mVertexArrays.size(); }

protected:



	// Vertex arrays associated with this mesh
	std::vector<VertexArray*> mVertexArrays;

	// Stores object space bounding sphere radius
	float mRadius;

};