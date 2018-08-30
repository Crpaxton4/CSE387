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
	Uint32 mTicksCount = 0;

	// Window Variables
	int windowHeight = 768;
	int windowWidth = 1024;

	// Game variables
	const vec2 DEFAULT_BALL_VEL = vec2(100.0f, 135.0f);
	const float LEFT_PADDLE_X = 10.0;
	const int THICKNESS = 15;
	const float PADDLE_HEIGHT = 100.0f;
	const float PADDLE_SPEED = 300.0;

	float rightPaddleX = windowWidth - THICKNESS - 10.0f;

	// Game should continue to run
	bool mIsRunning = true;

	// Pong specific
	// Direction of paddles
	int mLeftPaddleDir = 0;
	int mRightPaddleDir = 0;
	// Position of paddles
	vec2 mLeftPaddlePos;
	vec2 mRightPaddlePos;
	// Position of ball
	vec2 mBallPos;
	// Velocity of ball
	vec2 mBallVel;


};
