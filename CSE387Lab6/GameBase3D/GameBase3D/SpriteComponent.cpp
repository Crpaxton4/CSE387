// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "SharedProjectionAndViewing.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
	,spriteScale(mat4(1.0f ) )
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		// Since all sprites use the same shader/vertices,
		// the Renderer first sets them active before any sprite draws

		// Include the scale in the world transformation
		mat4 myWorld = mOwner->GetWorldTransform( ) * spriteScale;

		// Set world transform in the shader program
		shader->SetMatrixUniform( "uWorldTransform", myWorld );

		// Set current texture
		mTexture->SetActive();

		// Draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;

	// Set width/height
	mTexWidth = texture->GetWidth( );
	mTexHeight = texture->GetHeight( );

	// Scale the sprite according to the texture image dimensions
	spriteScale = glm::scale( vec3( static_cast<float>( mTexWidth ),
									static_cast<float>( mTexHeight ),
															1.0f ) );
}
