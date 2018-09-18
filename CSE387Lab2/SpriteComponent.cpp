// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent( Actor* owner, int drawOrder )
	:Component( owner ), 
	mDrawOrder( drawOrder )
{
	mOwner->GetGame( )->AddSprite( this );
}

SpriteComponent::~SpriteComponent( )
{
	mOwner->GetGame( )->RemoveSprite( this );
}

void SpriteComponent::Draw( SDL_Renderer* renderer )
{
	if( mTexture ) {
		SDL_Rect spriteBoundingRec;
		// Scale the width/height by owner's scale
		spriteBoundingRec.w = static_cast<int>( mTexWidth * mOwner->GetScale( ) );
		spriteBoundingRec.h = static_cast<int>( mTexHeight * mOwner->GetScale( ) );
		// Center the rectangle around the position of the owner
		spriteBoundingRec.x = static_cast<int>( mOwner->GetPosition( ).x - spriteBoundingRec.w / 2 );
		spriteBoundingRec.y = static_cast<int>( mOwner->GetPosition( ).y - spriteBoundingRec.h / 2 );

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		// See https://wiki.libsdl.org/SDL_RenderCopyEx
		SDL_RenderCopyEx( renderer,
			mTexture,
			nullptr,
			&spriteBoundingRec,
			-glm::degrees( mOwner->GetRotation( ) ),
			nullptr,
			SDL_FLIP_NONE );
	}
}

void SpriteComponent::SetTexture( SDL_Texture* texture )
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture( texture, nullptr, nullptr, &mTexWidth, &mTexHeight );
}
