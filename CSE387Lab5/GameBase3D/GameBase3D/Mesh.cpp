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

		// vertex positions
		glm::vec3 pos1 = glm::vec3(1, 1, 1);
		glm::vec3 pos2 = glm::vec3(1, 1, -1);
		glm::vec3 pos3 = glm::vec3(1, -1, 1);
		glm::vec3 pos4 = glm::vec3(1, -1, -1);
		glm::vec3 pos5 = glm::vec3(-1, 1, 1);
		glm::vec3 pos6 = glm::vec3(-1, 1, -1);
		glm::vec3 pos7 = glm::vec3(-1, -1, 1);
		glm::vec3 pos8 = glm::vec3(-1, -1, -1);

		// face normals
		glm::vec3 norm1 = glm::vec3(1, 0, 0);
		glm::vec3 norm2 = glm::vec3(-1, 0, 0);
		glm::vec3 norm3 = glm::vec3(0, 1, 0);
		glm::vec3 norm4 = glm::vec3(0, -1, 0);
		glm::vec3 norm5 = glm::vec3(0, 0, 1);
		glm::vec3 norm6 = glm::vec3(0, 0, -1);
		
		// texture coordinates
		glm::vec2 tex1 = glm::vec2(0, 0);
		glm::vec2 tex2 = glm::vec2(0, 1);
		glm::vec2 tex3 = glm::vec2(1, 0);
		glm::vec2 tex4 = glm::vec2(1, 1);

		// positive x face 
		pntVertexData face1p1 = pntVertexData(pos1, norm1, tex1); vData.push_back(face1p1); //0
		pntVertexData face1p2 = pntVertexData(pos2, norm1, tex2); vData.push_back(face1p2); //1
		pntVertexData face1p3 = pntVertexData(pos3, norm1, tex3); vData.push_back(face1p3); //2
		pntVertexData face1p4 = pntVertexData(pos4, norm1, tex4); vData.push_back(face1p4); //3

		//negative x face
		pntVertexData face2p1 = pntVertexData(pos5, norm2, tex1); vData.push_back(face2p1); //4
		pntVertexData face2p2 = pntVertexData(pos6, norm2, tex2); vData.push_back(face2p2); //5
		pntVertexData face2p3 = pntVertexData(pos7, norm2, tex3); vData.push_back(face2p3); //6
		pntVertexData face2p4 = pntVertexData(pos8, norm2, tex4); vData.push_back(face2p4); //7

		//positive y face
		pntVertexData face3p1 = pntVertexData(pos1, norm3, tex1); vData.push_back(face3p1); //8
		pntVertexData face3p2 = pntVertexData(pos2, norm3, tex2); vData.push_back(face3p2); //9
		pntVertexData face3p3 = pntVertexData(pos5, norm3, tex3); vData.push_back(face3p3); //10
		pntVertexData face3p4 = pntVertexData(pos6, norm3, tex4); vData.push_back(face3p4); //11

		//negative y face
		pntVertexData face4p1 = pntVertexData(pos3, norm4, tex1); vData.push_back(face4p1); //12
		pntVertexData face4p2 = pntVertexData(pos4, norm4, tex2); vData.push_back(face4p2); //13
		pntVertexData face4p3 = pntVertexData(pos7, norm4, tex3); vData.push_back(face4p3); //14
		pntVertexData face4p4 = pntVertexData(pos8, norm4, tex4); vData.push_back(face4p4); //15

		//positive z face
		pntVertexData face5p1 = pntVertexData(pos1, norm5, tex1); vData.push_back(face5p1); //16
		pntVertexData face5p2 = pntVertexData(pos3, norm5, tex2); vData.push_back(face5p2); //17
		pntVertexData face5p3 = pntVertexData(pos5, norm5, tex3); vData.push_back(face5p3); //18
		pntVertexData face5p4 = pntVertexData(pos7, norm5, tex4); vData.push_back(face5p4); //19

		//negative z face
		pntVertexData face6p1 = pntVertexData(pos2, norm6, tex1); vData.push_back(face6p1); //20
		pntVertexData face6p2 = pntVertexData(pos4, norm6, tex2); vData.push_back(face6p2); //21
		pntVertexData face6p3 = pntVertexData(pos6, norm6, tex3); vData.push_back(face6p3); //22
		pntVertexData face6p4 = pntVertexData(pos8, norm6, tex4); vData.push_back(face6p4); //23


		indices = {
			0, 2, 3,
			1, 3, 2,

			4, 5, 6,
			6, 7, 4,

			8, 9, 11,
			10, 11, 8,

			12, 14, 13, 
			12, 15, 13,

			16, 17, 18, 
			18, 19, 16, 

			20, 22, 23, 
			22, 23, 21
		};


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


