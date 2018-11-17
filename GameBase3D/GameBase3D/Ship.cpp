// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "SpaceGame.h"
#include "Laser.h"


Ship::Ship( SpaceGame* game )
	:SpaceGameActor( game )
	, mLaserCooldown( 0.0f )
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent( this, 150 );
	sc->SetTexture( game->GetTexture( "Assets/Ship.png" ) );

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent( this );
	ic->SetForwardKey( SDL_SCANCODE_W );
	ic->SetBackKey( SDL_SCANCODE_S );
	ic->SetClockwiseKey( SDL_SCANCODE_A );
	ic->SetCounterClockwiseKey( SDL_SCANCODE_D );
	ic->SetMaxForwardSpeed( 300.0f );
	ic->SetMaxAngularSpeed( TWO_PI );
}

void Ship::UpdateActor( float deltaTime )
{
	mLaserCooldown -= deltaTime;
}

void Ship::ActorInput( const uint8_t* keyState )
{
	if( keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f ) {
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser( GetSpaceGame( ) );
		laser->SetPosition( GetPosition( ) );
		laser->SetRotation( GetRotation( ) );

		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}
}
