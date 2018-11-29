// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent( class Actor* owner, class Mesh * mesh )
	:Component(owner)
	,mMesh( mesh )
{
	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);

	this->collisionShape = mesh->GetCollisionShape( );
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}


void MeshComponent::Draw(Shader* shader)
{
	if( mMesh ) {

		float s = mOwner->GetScale( );

		// Set the world transform
		SharedProjectionAndViewing::setModelingMatrix(mOwner->GetWorldTransformation() * glm::scale(vec3( s, s, s )));

		// For each mesh of the object, set the active vertex array object, associated
		// texture, and draw the the mesh onto the screen.
		for (int i = 0; i < mMesh->numberOfVertexArrayObjects(); i++)
		{
			// Set the material properties
			SharedMaterialProperties::setShaderMaterialProperties( mMesh->GetVertexArrays( )[i]->vaoMaterial );

			// Set the mesh's vertex array as active
			VertexArray* va = mMesh->GetVertexArrays( )[i];
			va->SetActive( );

			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

			// Clean up material settings in the shader to default values
			SharedMaterialProperties::cleanUpMaterial( mMesh->GetVertexArrays( )[i]->vaoMaterial );
		}
		
	}
}