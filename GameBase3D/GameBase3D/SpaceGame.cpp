#include "SpaceGame.h"
#include <GL/glew.h>
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"



SpaceGame::SpaceGame( )
	:Game( "CSE387 Chapter Five - Revised")
{
}


void SpaceGame::LoadData( )
{
	// Create player's ship
	mShip = new Ship( this );
	mShip->SetRotation( PI_OVER_2 );

	// Create asteroids
	const int numAsteroids = 20;
	for( int i = 0; i < numAsteroids; i++ ) {
		new Asteroid( this );
	}
}

void SpaceGame::AddAsteroid( Asteroid* ast )
{
	mAsteroids.emplace_back( ast );
}

void SpaceGame::RemoveAsteroid( Asteroid* ast )
{
	auto iter = std::find( mAsteroids.begin( ),
		mAsteroids.end( ), ast );
	if( iter != mAsteroids.end( ) ) {
		mAsteroids.erase( iter );
	}
}
