// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <string>
#include <vector>
#include "MathLibsConstsFuncs.h"

class Game
{

	public:
	Game(std::string windowTitle = "CSE387");
	~Game( );
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddChild(class Actor* actor);
	void RemoveActor(class Actor* actor);

	const std::string& GetWindowTitle( ) { return mWindowTitle;	}

	class Renderer* GetRenderer() { return mRenderer; }

protected:

	virtual void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	virtual void LoadData( ) { };
	virtual void UnloadData();
	
	// All the actors in the game
	std::vector<class Actor*> mActors;

	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	Uint32 mTicksCount;
	bool mIsRunning;

	// Track if we're updating actors right now
	bool mUpdatingActors;

	class Renderer* mRenderer;

	// Title for the window
	std::string mWindowTitle;

};
