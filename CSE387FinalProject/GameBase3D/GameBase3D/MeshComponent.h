// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include <cstddef>

class MeshComponent : public Component
{
public:
	MeshComponent(class Actor* owner, class Mesh * mesh);

	~MeshComponent();

	// Draw this mesh component
	virtual void Draw(class Shader* shader);

	//// Set the mesh/texture index used by mesh component
	//virtual void SetMesh( class Mesh* mesh );

	virtual class btCollisionShape * GetCollisionShape( ) const { return collisionShape; }

protected:
	class Mesh* mMesh;

	class btCollisionShape * collisionShape;

};
