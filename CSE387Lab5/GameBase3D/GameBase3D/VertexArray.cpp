// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray( const std::vector<pntVertexData> & vertexData, const std::vector<unsigned int> & indices )
{
	//TODO
	// generate and bind vertex array object
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	 //Buffer for potitions
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	//For vertex positions
	// load the vertex positions into a buffer
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(pntVertexData), &vertexData[0], GL_STATIC_DRAW);
	//specify location and data format of an aray of vertex options
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	//Enable floaw of the vertex attribute array to specified vertex attribute location
	glEnableVertexAttribArray(0);

	//For vertex normals
	//specify location and data format of an aray of vertex options
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const void*)sizeof(glm::vec3));
	//Enable floaw of the vertex attribute array to specified vertex attribute location
	glEnableVertexAttribArray(1);

	//For vertex texture coords
	//specify location and data format of an aray of vertex options
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const void*)(2*sizeof(glm::vec3)));
	//Enable floaw of the vertex attribute array to specified vertex attribute location
	glEnableVertexAttribArray(2);

	// Save the number of verticies of the actual rendering call
	mNumVerts = vertexData.size();


	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	mNumIndices = indices.size();
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
