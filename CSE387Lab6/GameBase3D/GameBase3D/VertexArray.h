// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "MathLibsConstsFuncs.h"
#include <vector>
#include "SharedMaterialProperties.h"

struct pntVertexData
{
	glm::vec3 m_pos;
	glm::vec3 m_normal;
	glm::vec2 m_textCoord;

	pntVertexData( ) { }

	pntVertexData( glm::vec3 pos, glm::vec3 normal, glm::vec2 textCoord )
	{
		m_pos = pos;
		m_normal = normal;
		m_textCoord = textCoord;

	}
};


class VertexArray
{
public:
	VertexArray( const std::vector<pntVertexData> & vertexData, const std::vector<unsigned int> & indices );

	~VertexArray();

	// Activate this vertex array (so we can draw it)
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

	Material vaoMaterial;

private:
	// How many vertices in the vertex buffer?
	unsigned int mNumVerts;
	// How many indices in the index buffer
	unsigned int mNumIndices;
	// OpenGL ID of the vertex buffer
	unsigned int mVertexBuffer;
	// OpenGL ID of the index buffer
	unsigned int mIndexBuffer;
	// OpenGL ID of the vertex array object
	unsigned int mVertexArray;
};