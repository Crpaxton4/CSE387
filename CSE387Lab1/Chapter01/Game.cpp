// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"



Game::Game()
	: mWindow(nullptr),
	mRenderer(nullptr),
	mTicksCount(0),
	mIsRunning(true),
	mPaddleDir(0) {}

bool Game::Initialize() {
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an SDL Window
	mWindow =
		SDL_CreateWindow("CSE 387 Introduction (Chapter 1)",  // Window title
			100,   // Top left x-coordinate of window
			100,   // Top left y-coordinate of window
			1024,  // Width of window
			768,   // Height of window
			0      // Flags (0 for no flags set)
		);

	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create SDL renderer
	mRenderer =
		SDL_CreateRenderer(mWindow,  // Window to create renderer for
			-1,       // Usually -1
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	mPaddlePos.x = PADDLE_X;
	mPaddlePos.y = WINDOW_HEIGHT / 2.0f;
	mBallPos.x = WINDOW_WIDTH/ 2.0f;
	mBallPos.y = WINDOW_HEIGHT / 2.0f;
	mBallVel = DEFAULT_BALL_VEL;
	
	return true;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) {
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S]) {
		mPaddleDir += 1;
	}
}

void Game::UpdateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Update paddle position based on direction
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (PADDLE_HEIGHT / 2.0f + THICKNESS)) {
			mPaddlePos.y = PADDLE_HEIGHT / 2.0f + THICKNESS;
		}
		else if (mPaddlePos.y > (WINDOW_HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS)) {
			mPaddlePos.y = WINDOW_HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS;
		}
	}

	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= PADDLE_HEIGHT / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f) {
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f) {
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (WINDOW_WIDTH- THICKNESS) && mBallVel.x > 0.0f) {
		mBallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= THICKNESS && mBallVel.y < 0.0f) {
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (WINDOW_HEIGHT - THICKNESS) && mBallVel.y > 0.0f) {
		mBallVel.y *= -1;
	}
}

void Game::GenerateOutput() {
	// Set draw color to blue
	SDL_SetRenderDrawColor(mRenderer,
		0,    // R
		0,    // G
		255,  // B
		255   // A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// Draw top wall
	SDL_Rect wall{
		0,         // Top left x
		0,         // Top left y
		WINDOW_WIDTH,      // Width
		THICKNESS  // Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = WINDOW_HEIGHT - THICKNESS;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = WINDOW_WIDTH - THICKNESS;
	wall.y = 0;
	wall.w = THICKNESS;
	wall.h = WINDOW_WIDTH;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	SDL_Rect paddle{ static_cast<int>(mPaddlePos.x),
					static_cast<int>(mPaddlePos.y - PADDLE_HEIGHT / 2), THICKNESS,
					static_cast<int>(PADDLE_HEIGHT) };
	SDL_RenderFillRect(mRenderer, &paddle);

	// Draw ball
	SDL_Rect ball{ static_cast<int>(mBallPos.x - THICKNESS / 2),
				  static_cast<int>(mBallPos.y - THICKNESS / 2), THICKNESS,
				  THICKNESS };
	SDL_RenderFillRect(mRenderer, &ball);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
