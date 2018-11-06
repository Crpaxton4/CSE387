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
#include <fstream>
#include <sstream>
#include <SDL/SDL_log.h>
#include "MathLibsConstsFuncs.h"
#include <iostream>


Mesh::Mesh()
	:mRadius(0.0f)
{
}

Mesh::~Mesh()
{
}


void Mesh::Unload()
{
	for (VertexArray* mVertexArray : mVertexArrays)
	{
		delete mVertexArray;
		mVertexArray = nullptr;
	}
	mVertexArrays.clear();
	
}
