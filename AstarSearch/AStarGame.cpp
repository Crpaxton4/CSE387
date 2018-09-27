#include "AStarGame.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Grid.h"
#include "Enemy.h"
#include "AIComponent.h"
#include "AIState.h"
#include "AnimSpriteComponent.h"
#include "MultiAnimSpriteComponent.h"
#include "MyMultiActor.h"
#include "SpriteSheetAnimCompnent.h"
#include "EqualWeightEdgeGraph.h"
#include <iostream>


AStarGame::AStarGame( )
{
}


AStarGame::~AStarGame( )
{
}


void AStarGame::ProcessInput( )
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState( NULL );
	if( keyState[SDL_SCANCODE_ESCAPE] ) {
		mIsRunning = false;
	}

	if( keyState[SDL_SCANCODE_B] ) {
		mGrid->BuildTower( );
	}

	// Process mouse
	int x, y;
	Uint32 buttons = SDL_GetMouseState( &x, &y );
	if( SDL_BUTTON( buttons ) & SDL_BUTTON_LEFT ) {
		mGrid->ProcessClick( x, y );
	}

	mUpdatingActors = true;
	for( auto actor : mActors ) {
		actor->ProcessInput( keyState );
	}
	mUpdatingActors = false;
}

void AStarGame::LoadData( )
{
	mGrid = new Grid(this);

	EqualWeightEdgeGraph * equalWeightGraph = new EqualWeightEdgeGraph( this );

}

Enemy* AStarGame::GetNearestEnemy( const vec2& pos )
{
	Enemy* best = nullptr;

	if( mEnemies.size( ) > 0 ) {
		best = mEnemies[0];
		// Save the distance squared of first enemy, and test if others are closer
		vec2 bestDiffVector = pos - mEnemies[0]->GetPosition( );
		float bestDistSq = glm::dot( bestDiffVector, bestDiffVector );
		for( size_t i = 1; i < mEnemies.size( ); i++ ) {
			vec2 diffVector = pos - mEnemies[i]->GetPosition( );
			float newDistSq = glm::dot( diffVector, diffVector );

			if( newDistSq < bestDistSq ) {
				bestDistSq = newDistSq;
				best = mEnemies[i];
			}
		}
	}

	return best;
}
