// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

#include <iostream>
#include <algorithm>
#include "Renderer.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Random.h"
#include "SoundEngine.h"
#include "PhysicsEngine.h"

Game::Game( std::string windowTitle )
	: mIsRunning( true ), mUpdatingActors( false ), mWindowTitle( windowTitle )
{
}

Game::~Game( )
{
	// Stop the sound engine
	SoundEngine::Stop( );

	// Stop the physics engine
	PhysicsEngine::Stop( );
}

bool Game::Initialize( )
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 ) {
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError( ) );
		return false;
	}

	// Create the renderer
	mRenderer = new Renderer( this );

	if( !mRenderer->Initialize( 1024, 768 ) ) {
		SDL_Log( "Failed to initialize renderer" );
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	// Initialize the sound engine
	SoundEngine::Init( );

	// Initialize the physics engine
	PhysicsEngine::Init( );

	LoadData( );

	mTicksCount = SDL_GetTicks( );

	return true;
}

void Game::RunLoop( )
{
	while( mIsRunning ) {
		ProcessInput( );
		UpdateGame( );
		GenerateOutput( );
	}
}

void Game::ProcessInput( )
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) {
		if( event.type == SDL_WINDOWEVENT ) { // Windows event?

			switch( event.window.event ) {

				case SDL_WINDOWEVENT_SIZE_CHANGED:

					mRenderer->Resize( );

					break;
			}
		}
		else {

			switch( event.type ) {

				// If we get an SDL_QUIT event, end loop
				case SDL_QUIT:
					std::cout << "Window closed. Quitting." << std::endl;
					mIsRunning = false;
					break;
			}
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState( NULL );
	if( keyState[SDL_SCANCODE_ESCAPE] ) {
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for( auto actor : mActors ) {
		actor->ProcessInput( keyState );
	}
	mUpdatingActors = false;
}

void Game::UpdateGame( )
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while( !SDL_TICKS_PASSED( SDL_GetTicks( ), mTicksCount + 16 ) );
	;

	float deltaTime = ( SDL_GetTicks( ) - mTicksCount ) / 1000.0f;
	if( deltaTime > 0.05f ) {
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks( );

	// Updates the position and orientation of actors based on
	// positions, velocities, and collisions
	PhysicsEngine::Update( deltaTime );

	// Update all actors
	mUpdatingActors = true;
	for( auto actor : mActors ) {
		actor->Update( deltaTime );
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for( auto pending : mPendingActors ) {
		pending->ComputeLocalTransform( );
		mActors.emplace_back( pending );
	}
	mPendingActors.clear( );

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for( auto actor : mActors ) {
		if( actor->GetState( ) == Actor::EDead ) {
			deadActors.emplace_back( actor );
		}
	}

	// Delete dead actors (which removes them from mActors)
	for( auto actor : deadActors ) {
		delete actor;
	}

	// Updates the FMOD system based on the current position and orientations
	// of the SoundSources and SoundListeners
	SoundEngine::Update( deltaTime );
}

void Game::GenerateOutput( )
{
	mRenderer->Draw( );
}



void Game::UnloadData( )
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while( !mActors.empty( ) ) {
		delete mActors.back( );
	}

	if( mRenderer ) {
		mRenderer->UnloadData( );
	}

}



void Game::Shutdown( )
{
	UnloadData( );

	if( mRenderer ) {
		mRenderer->Shutdown( );
	}

	SDL_Quit( );
}

void Game::AddChild( Actor* actor )
{
	// If we're updating actors, need to add to pending
	if( mUpdatingActors ) {
		mPendingActors.emplace_back( actor );
	}
	else {
		mActors.emplace_back( actor );
	}
}

void Game::RemoveActor( Actor* actor )
{
	// Is it in pending actors?
	auto iter = std::find( mPendingActors.begin( ), mPendingActors.end( ), actor );
	if( iter != mPendingActors.end( ) ) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap( iter, mPendingActors.end( ) - 1 );
		mPendingActors.pop_back( );
	}

	// Is it in actors?
	iter = std::find( mActors.begin( ), mActors.end( ), actor );
	if( iter != mActors.end( ) ) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap( iter, mActors.end( ) - 1 );
		mActors.pop_back( );
	}
}
