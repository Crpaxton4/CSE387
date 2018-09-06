// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
	public:

	bool Initialize( );
	void RunLoop( );
	void Shutdown( );

	// Adds an Actor to either the current or pending Actors vector
	// depending on whether or not an update cycle is in progress
	void AddActor( class Actor* actor );

	// Removes an Actor from ether the the current or pending Actors vector is found
	void RemoveActor( class Actor* actor );

	// Add a SpriteComponent to the Sprite vector depending on rendering order
	void AddSprite( class SpriteComponent* sprite );

	// Removes a SpriteComponent from the sprite vector
	void RemoveSprite( class SpriteComponent* sprite );

	// Loads textures for a specified path and file name
	SDL_Texture* GetTexture( const std::string& fileName );

	protected:
	void ProcessInput( );
	void UpdateGame( );
	void GenerateOutput( );
	void UnloadData( );

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the Actors currently in the game
	std::vector<class Actor*> mCurrentActors;

	// Any pending Actors to be added after the current update cycle
	std::vector<class Actor*> mPendingActors;

	// All the sprite Components to be drawn
	// vector is ordered based on sprite draw order values
	std::vector<class SpriteComponent*> mSprites;

	// Window created by SDL
	SDL_Window* mWindow = nullptr;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer = nullptr;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run if true
	bool mIsRunning = true;

	// Track if we're updating actors right now
	bool mUpdatingActors = false;

	const unsigned int mWindowPositionX = 100;
	const unsigned int mWindowPositionY = 100;
	const unsigned int mWindowWidth = 1024;
	const unsigned int mWindowHeight = 768;
	std::string windowTitle = "Space";
};
