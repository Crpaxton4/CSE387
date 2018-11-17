// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"


bool Game::Initialize( )
{
	// Initialize SDL. Exit if unsucessful
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 ) {
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError( ) );
		return false;
	}

	// Create an SDL Window. Exit if unsucessful
	mWindow = SDL_CreateWindow( windowTitle.c_str(), mWindowPositionX, mWindowPositionY, mWindowWidth, mWindowHeight, 0 );

	if( !mWindow ) {
		SDL_Log( "Failed to create window: %s", SDL_GetError( ) );
		return false;
	}

	// Create SDL renderer for 2D rendering. Exit if unsucessful
	mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( !mRenderer ) {
		SDL_Log( "Failed to create renderer: %s", SDL_GetError( ) );
		return false;
	}

	// Initialize the SDL image library to load PNG files.
	if( IMG_Init( IMG_INIT_PNG ) == 0 ) {
		SDL_Log( "Unable to initialize SDL_image: %s", SDL_GetError( ) );
		return false;
	}

	// Get unsigned 32-bit value representing the number of milliseconds
	// since the SDL library initialized
	mTicksCount = SDL_GetTicks( );

	LoadData();

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
	// Function needs to be overridden. Probably bad practice.
}

void Game::UpdateGame( )
{
	// Busy Loop
	// Wait until 16ms has elapsed since last frame
	while( !SDL_TICKS_PASSED( SDL_GetTicks( ), mTicksCount + 16 ) ) { };

	// Compute delta time. Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = ( SDL_GetTicks( ) - mTicksCount ) / 1000.0f;
	
	// Clamp maximum delta time value to avoid huge updates following pauses
	if( deltaTime > 0.05f ) {
		deltaTime = 0.05f;
	}

	// Get the number of ticks for next update
	mTicksCount = SDL_GetTicks( );

	// Set flag to indicate actors are being updated
	mUpdatingActors = true;

	// Update all actors
	for( auto actor : mCurrentActors ) {
		actor->Update( deltaTime );
	}

	// Set flag to indicate actor updating has been completed
	mUpdatingActors = false;

	// Add any pending actors to vector of current actors
	for( auto pending : mPendingActors ) {
		mCurrentActors.emplace_back( pending );
	}
	mPendingActors.clear( );

	// Generate a vector of dead actors
	std::vector<Actor*> deadActors;
	for( auto actor : mCurrentActors ) {
		if( actor->GetState( ) == Actor::EDead ) {
			deadActors.emplace_back( actor );
		}
	}

	// Delete dead actors 
	// Actor destructor removes them from mCurrentActors
	for( auto actor : deadActors ) {
		delete actor;
	}
}

void Game::GenerateOutput( )
{
	// Set the background color to black
	SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 255 );

	// Clear back buffer
	SDL_RenderClear( mRenderer );

	// Draw all sprite components
	// Sprint with the lowest draw order are rendered first
	for( auto sprite : mSprites ) {
		sprite->Draw( mRenderer );
	}

	// Swap front buffer and back buffer
	SDL_RenderPresent( mRenderer );
}

void Game::LoadData() {
	// Function needs to be overridden. Probably bad practice
}

void Game::UnloadData( )
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while( !mCurrentActors.empty( ) ) {
		delete mCurrentActors.back( );
	}

	// Destroy textures
	for( auto i : mTextures ) {
		SDL_DestroyTexture( i.second );
	}
	mTextures.clear( );
}

SDL_Texture* Game::GetTexture( const std::string& fileName )
{
	SDL_Texture* tex = nullptr; // texture to be loaded

	// Check map of loaded textures to see if the texture has already been loaded
	auto iter = mTextures.find( fileName );

	// Is the texture already in the map?
	if( iter != mTextures.end( ) ) {

		// Set tex to the already loaded version of the texture
		tex = iter->second;
	}
	else {
		// Load from file to create an SDL surface
		SDL_Surface* surf = IMG_Load( fileName.c_str( ) );
		if( !surf ) {
			SDL_Log( "Failed to load texture file %s", fileName.c_str( ) );
			return nullptr;
		}

		// Create a texture using the surface
		tex = SDL_CreateTextureFromSurface( mRenderer, surf );
		SDL_FreeSurface( surf );
		if( !tex ) {
			SDL_Log( "Failed to convert surface to texture for %s", fileName.c_str( ) );
			return nullptr;
		}

		// Save the texture name in the map to avoid loading it multiple times
		mTextures.emplace( fileName.c_str( ), tex );
	}
	return tex;
}

void Game::Shutdown( )
{
	UnloadData( );
	IMG_Quit( );
	SDL_DestroyRenderer( mRenderer );
	SDL_DestroyWindow( mWindow );
	SDL_Quit( );
}

void Game::AddActor( Actor* actor )
{
	// Is the game in the process of updating the Actors?
	if( mUpdatingActors == true ) {

		// If we're updating actors, need to add to pending
		mPendingActors.emplace_back( actor );
	}
	else { 

		// Not in the update cycle. Add to the current actors in the game
		mCurrentActors.emplace_back( actor );
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
	iter = std::find( mCurrentActors.begin( ), mCurrentActors.end( ), actor );
	if( iter != mCurrentActors.end( ) ) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap( iter, mCurrentActors.end( ) - 1 );
		mCurrentActors.pop_back( );
	}
}

void Game::AddSprite( SpriteComponent* sprite )
{
	// Get the draw order of the sprite
	int myDrawOrder = sprite->GetDrawOrder( );

	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	// Sprited with the lowest draw order are rendered first
	auto iter = mSprites.begin( );
	for( ; iter != mSprites.end( ); ++iter ) {
		
		if( myDrawOrder < ( *iter )->GetDrawOrder( ) ) {
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert( iter, sprite );
}

void Game::RemoveSprite( SpriteComponent* sprite )
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find( mSprites.begin( ), mSprites.end( ), sprite );
	mSprites.erase( iter );
}
