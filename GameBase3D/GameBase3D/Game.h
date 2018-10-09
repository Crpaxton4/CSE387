// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "MathLibsConstsFuncs.h"

class Game
{
public:
	Game(std::string windowTitle = "CSE387");
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	
	class Texture* GetTexture(const std::string& fileName);

	int getWindowWidth( ) { return mWindowWidth; };
	int getWindowHeight( ) { return mWindowHeight; };

protected:
	virtual void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	virtual void LoadData( ) { };
	virtual void UnloadData();
	
	// Map of textures loaded
	std::unordered_map<std::string, class Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	// Sprite shader
	class Shader* mSpriteShader;
	// Sprite vertex array
	class VertexArray* mSpriteVerts;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Title for the window
	std::string mWindowTitle;

	// Current window width and height
	int mWindowWidth = 1024;
	int mWindowHeight = 768;

	// Current window clear color
	vec4 mClearColor = vec4( 0.86f, 0.86f, 0.86f, 1.0f );
};
