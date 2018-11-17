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

class Mesh
{
public:
	Mesh();
	~Mesh();

	// Load/unload mesh
	bool Load(class Renderer* renderer, const std::string & fileName = "");
	void Unload();

	// Get the vertex array associated with this mesh
	class VertexArray* GetVertexArray() { return mVertexArray; }

	// Get a texture from specified index
	class Texture* GetTexture( ) { return mTexture; }

	// Get a texture from specified index
	void SetTexture(Texture * texture ) { mTexture = texture; }

	// Get name of shader
	const std::string& GetShaderName() const { return mShaderName; }

	// Get object space bounding sphere radius
	float GetRadius() const { return mRadius; }

private:

	// Textures associated with this mesh
	class Texture* mTexture = nullptr;

	// Vertex array associated with this mesh
	class VertexArray* mVertexArray;

	// Name of shader specified by mesh
	std::string mShaderName;

	// Stores object space bounding sphere radius
	float mRadius;

};