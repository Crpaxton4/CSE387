// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <iostream>

#include "SDL/SDL.h"

// Forward declaration to speed compilation
#include "glm/fwd.hpp"

// In a source file using GLM types
#include "glm/glm.hpp"

// Stable glm extensions
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

#define PI glm::pi<float>()

// Game class
class Game {
public:
	Game();

	// Initialize the game
	bool Initialize();

	// Runs the game loop until the game is over
	void RunLoop();

	// Shutdown the game
	void Shutdown();

private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow = nullptr;

	// Renderer for 2D drawing
	SDL_Renderer* mRenderer = nullptr;

	// Number of ticks since start of game
	Uint32 mTicksCount;

	// Game constsnts
	const float WINDOW_HEIGHT = 768.0;
	const float WINDOW_WIDTH = 1024.0;
	const vec2 DEFAULT_BALL_VEL = vec2(-200.0f, 235.0f);
	const float PADDLE_X = 10.0;
	const int THICKNESS = 15;
	const float PADDLE_HEIGHT = 100.0f;


	// Game should continue to run
	bool mIsRunning;

	// Pong specific
	// Direction of paddle
	int mPaddleDir;
	// Position of paddle
	vec2 mPaddlePos;
	// Position of ball
	vec2 mBallPos;
	// Velocity of ball
	vec2 mBallVel;


};
