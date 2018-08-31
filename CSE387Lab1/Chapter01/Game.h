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

	void drawCenterLine(int r, int g, int b, int a);

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
	const int DEFAULT_WINDOW_WIDTH = 1024;
	const int DEFAULT_WINDOW_HEIGHT = 768;
	int windowWidth = DEFAULT_WINDOW_WIDTH;
	int windowHeight = DEFAULT_WINDOW_HEIGHT;
	

	// Game variables
	const vec2 DEFAULT_BALL_VEL = vec2(200.0f, 300. 0f);
	const float LEFT_PADDLE_X = 10.0;
	int verticalThickness = 15;
	int horizontalThickness = 15;
	float paddleHeight = 100.0f;
	const float PADDLE_SPEED = 300.0;
	int ballThickness = static_cast<int>(15.0f *((float)windowWidth + (float)windowHeight) / ((float)DEFAULT_WINDOW_WIDTH + (float)DEFAULT_WINDOW_HEIGHT));

	float rightPaddleX = windowWidth - horizontalThickness - 10.0f;

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
