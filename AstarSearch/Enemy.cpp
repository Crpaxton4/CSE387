// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "AStarGame.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy( class Game* game )
	:Actor( game )
{
	// Add to enemy vector
	( (AStarGame*)game )->GetEnemies( ).emplace_back( this );

	SpriteComponent* sc = new SpriteComponent( this );
	sc->SetTexture( game->GetTexture( "Assets/Airplane.png" ) );
	// Set position at start tile
	SetPosition( ( (AStarGame*)GetGame( ) )->GetGrid( )->GetStartTile( )->GetPosition( ) );
	
	// Setup a nav component at the start tile
	NavComponent* nc = new NavComponent( this );
	nc->SetForwardSpeed( 150.0f );

	nc->StartPath( ( (AStarGame*)GetGame( ) )->GetGrid( )->GetStartTile( ) );
	// Setup a circle for collision
	mCircle = new CircleComponent( this );
	mCircle->SetRadius( 25.0f );
}

Enemy::~Enemy( )
{
	// Remove from enemy vector
	auto iter = std::find( ( (AStarGame*)GetGame( ) )->GetEnemies( ).begin( ),
		( (AStarGame*)GetGame( ) )->GetEnemies( ).end( ),
		this );
	( (AStarGame*)GetGame( ) )->GetEnemies( ).erase( iter );
}

void Enemy::UpdateActor( float deltaTime )
{
	Actor::UpdateActor( deltaTime );

	// Am I near the end tile?
	vec2 diff = GetPosition( ) - ( (AStarGame*)GetGame( ) )->GetGrid( )->GetEndTile( )->GetPosition( );

	// Mark for deleation when at the goal
	if( NearZero( glm::length( diff ), 10.0f ) ) {
		SetState( EDead );
	}
}
