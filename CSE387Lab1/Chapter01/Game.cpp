// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

bool Game::Initialize() {
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	Uint32 windowFlags = SDL_WINDOW_RESIZABLE;

	// Create an SDL Window
	mWindow =
		SDL_CreateWindow("CSE 387 Introduction (Chapter 1)",  // Window title
			100,   // Top left x-coordinate of window
			100,   // Top left y-coordinate of window
			windowWidth,  // Width of window
			windowHeight,   // Height of window
			windowFlags      // Flags
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

	// TODO: use vec2 constructor to make this less busy

	mLeftPaddlePos.x = LEFT_PADDLE_X;
	mLeftPaddlePos.y = windowHeight / 2.0f;
	mRightPaddlePos.x = rightPaddleX;
	mRightPaddlePos.y = windowHeight / 2.0f;

	mBallPos.x = windowWidth / 2.0f;
	mBallPos.y = windowHeight / 2.0f;
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

		if (event.type == SDL_QUIT) {
			mIsRunning = false;
		}

		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);
				float heightScaleRatio = (float)windowHeight / (float)DEFAULT_WINDOW_HEIGHT;
				float widthScaleRatio = (float)windowWidth / (float)DEFAULT_WINDOW_WIDTH;


				//TODO: add a vertical thickness and a horizontal thickness so that the paddles and walls scale properly
				
				verticalThickness =  static_cast<int>(15.0f * heightScaleRatio);
				horizontalThickness = static_cast<int>(15.0f * widthScaleRatio);
				ballThickness = static_cast<int>(15.0f *((float)windowWidth + (float)windowHeight) / ((float)DEFAULT_WINDOW_WIDTH + (float)DEFAULT_WINDOW_HEIGHT));

				// move right paddle
				mRightPaddlePos.x = windowWidth - horizontalThickness - 10.0f;

				break;
			}
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	// Update paddle direction based on W/S keys
	if (state[SDL_SCANCODE_W]) {
		mLeftPaddleDir = -1;
	}

	if (state[SDL_SCANCODE_S]) {
		mLeftPaddleDir = 1;
	}

	if (state[SDL_SCANCODE_I]) {
		mRightPaddleDir = -1;
	}

	if (state[SDL_SCANCODE_K]) {
		mRightPaddleDir = 1;
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

	// Update left paddle position based on direction
	if (mLeftPaddleDir != 0) {
		mLeftPaddlePos.y += mLeftPaddleDir * PADDLE_SPEED * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mLeftPaddlePos.y < (paddleHeight / 2.0f + horizontalThickness)) {
			mLeftPaddlePos.y = paddleHeight / 2.0f + horizontalThickness;
		}
		else if (mLeftPaddlePos.y > (windowHeight - paddleHeight / 2.0f - horizontalThickness)) {
			mLeftPaddlePos.y = windowHeight - paddleHeight / 2.0f - horizontalThickness;
		}
	}

	// Update right paddle position based on direction
	if (mRightPaddleDir != 0) {
		mRightPaddlePos.y += mRightPaddleDir * PADDLE_SPEED * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mRightPaddlePos.y < (paddleHeight / 2.0f + horizontalThickness)) {
			mRightPaddlePos.y = paddleHeight / 2.0f + horizontalThickness;
		}
		else if (mRightPaddlePos.y > (windowHeight - paddleHeight / 2.0f - horizontalThickness)) {
			mRightPaddlePos.y = windowHeight - paddleHeight / 2.0f - horizontalThickness;
		}
	}

	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Bounce if needed

	// Did we intersect with the left paddle?
	float diffLeft = mLeftPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diffLeft = (diffLeft > 0.0f) ? diffLeft : -diffLeft;

	if (
		// Our y-difference is small enough
		diffLeft <= paddleHeight / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f) {

		mBallVel.x *= -1.0f;
	}

	// Did we intersect with the right paddle?
	float diffRight = mRightPaddlePos.y - mBallPos.y;

	// Take absolute value of difference
	diffRight = (diffRight > 0.0f) ? diffRight : -diffRight;

	if (
		// Our y-difference is small enough
		diffRight <= paddleHeight / 2.0f &&
		// We are in the correct x-position
		mBallPos.x >= windowWidth - horizontalThickness - 10.0f && mBallPos.x <= windowWidth - horizontalThickness - 5.0f && 
		
		/// This colission math is semi arbitraty so for consistency its a difference of 5.0f for some reason
		/// The ball dips a little past an objects borders (the math leads me to believe 10.0f past the border)
		///  I believe that is where the 'random' difference of 5 insead of THICKNESS (which is 15.0f)

		// The ball is moving to the Right
		mBallVel.x > 0.0f) {

		mBallVel.x *= -1.0f;
	}


	// Did the ball go off the left or right side of the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f || mBallPos.x >= windowWidth) {
		mIsRunning = false;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= verticalThickness && mBallVel.y < 0.0f) {
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (windowHeight - verticalThickness) && mBallVel.y > 0.0f) {
		mBallVel.y *= -1;
	}

	mLeftPaddleDir = 0;     // Stop Paddle so that when key is not pressed paddle stops
	mRightPaddleDir = 0;   // Probably not the best way to do this, but most of this file isn't the best either
}

void Game::GenerateOutput() {

	// Set draw color to blue
	SDL_SetRenderDrawColor(mRenderer,
		166,  // R
		128,  // G
		100,  // B
		255   // A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 
		183, // R
		65,  // G
		14,  // B
		255  // A
	);

	// Draw top wall
	SDL_Rect wall{
		0,         // Top left x
		0,         // Top left y
		windowWidth,      // Width
		verticalThickness  // Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = windowHeight - verticalThickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw left paddle
	SDL_Rect leftPaddle{ static_cast<int>(mLeftPaddlePos.x),
					static_cast<int>(mLeftPaddlePos.y - paddleHeight / 2), horizontalThickness,
					static_cast<int>(paddleHeight) };
	SDL_RenderFillRect(mRenderer, &leftPaddle);

	// Draw Right paddle
	SDL_Rect rightPaddle{ static_cast<int>(mRightPaddlePos.x),
					static_cast<int>(mRightPaddlePos.y - paddleHeight / 2), horizontalThickness,
					static_cast<int>(paddleHeight) };
	SDL_RenderFillRect(mRenderer, &rightPaddle);

	// Draw ball
	SDL_Rect ball{ static_cast<int>(mBallPos.x - ballThickness / 2),
				  static_cast<int>(mBallPos.y - ballThickness / 2), ballThickness,
				  ballThickness };
	SDL_RenderFillRect(mRenderer, &ball);

	drawCenterLine(133, 94, 66, 255);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);

}

void Game::drawCenterLine(int r, int g, int b, int a) {

	SDL_SetRenderDrawColor(mRenderer,
		r,
		g,
		b,
		a 
	);

	for (int i = 0; i < 10; i++) {
		SDL_Rect dash;

		dash.x = windowWidth / 2 - horizontalThickness / 2;
		dash.y = i * (windowHeight / 10);
			
		dash.w = horizontalThickness;
		dash.h = static_cast<int>((float)windowHeight / 20.0f);

		SDL_RenderFillRect(mRenderer, &dash);
	}
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
