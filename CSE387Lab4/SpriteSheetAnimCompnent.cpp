#include "SpriteSheetAnimCompnent.h"
#include "Actor.h"
#include "Game.h"

#include <iostream>

SpriteSheetAnimCompnent::SpriteSheetAnimCompnent( class Actor* owner, int drawOrder )
	:SpriteComponent( owner, drawOrder )
{

}


void SpriteSheetAnimCompnent::Update( float deltaTime )
{
	// Call the super class update
	SpriteComponent::Update( deltaTime );

		// Increment the display time of this frame
		frameTime += deltaTime;

		// Check if frame has been display long enough
		if( frameTime >= (1.0f / mAnimFPS) ) {

			// Update source rectange for next frame
			GetNextAnimationFrame( );

			// Reset display time for next frame
			frameTime = 0.0f;
		}
}

void SpriteSheetAnimCompnent::Draw( SDL_Renderer* renderer )
{
	if( mTexture ) {
		SDL_Rect r;
		// Scale the width/height by owner's scale and the frame size.
		r.w = static_cast<int>( currentAnimation.frameSize.x * mOwner->GetScale( ) );
		r.h = static_cast<int>( currentAnimation.frameSize.y * mOwner->GetScale( ) );
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>( mOwner->GetPosition( ).x - r.w / 2 );
		r.y = static_cast<int>( mOwner->GetPosition( ).y - r.h / 2 );

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx( renderer,
			mTexture,
			&sourceRectangle,
			&r,
			-glm::degrees( mOwner->GetRotation( ) ),
			nullptr,
			mFlip
		);
	}
}

void SpriteSheetAnimCompnent::AddAnimation( const std::string animationName, SpriteSheetAnimation animation, bool calcFrameSize)
{
	// Load the sprite sheet texture
	animation.spriteTexture = this->mOwner->GetGame()->GetTexture( animation.textureName.c_str());

	if( calcFrameSize == true ) {

		// Determine the dimensions of the texture
		int w, h;
		SDL_QueryTexture( animation.spriteTexture, NULL, NULL, &w, &h );

		// Save the dimensions of the texture 
		animation.dimensions = vec2( w, h );

		// Set the dimensions for the frame based on number of row and columns and resolution of the 
		// sprite sheet.
		animation.frameSize.x = animation.dimensions.x / animation.rowColumns.x;
		animation.frameSize.y = animation.dimensions.y / animation.rowColumns.y;
	}

	// Add the animation data to the map
	mAnimationMap.emplace( animationName, animation );
}

void SpriteSheetAnimCompnent::PlayAnimation( const std::string animationName )
{
	// Find the Animation in the map
	auto iter = mAnimationMap.find( animationName );

	// Check if it was found
	if( iter != mAnimationMap.end( ) ) {

		// Get the AnimationData struct
		currentAnimation = iter->second;

		// Set the texture for the animation
		SetTexture( currentAnimation.spriteTexture );

		// Set the beginning of the animation
		currentFrame = currentAnimation.startingFrame;

		// Set the frames per second for the animation
		mAnimFPS = currentAnimation.framePerSec;

		// Reset the frame display time
		frameTime = 0.0f;

		// Reset repeat counter
		repeatCount = 0;
	}
	else {
		SDL_Log( "Could not find %s in animation map", animationName.c_str( ) );
	}
}

void SpriteSheetAnimCompnent::GetNextAnimationFrame( )
{
	// Check if animation has been repeated a max number of times
	if( repeatCount < currentAnimation.loopTimes || currentAnimation.loopTimes == -1 ) {

		// Check if ending frame was reached
		if( currentFrame == currentAnimation.endingFrame ) {

			// Go back to the starting frame
			currentFrame = currentAnimation.startingFrame;
			// Increment the number of repeats of this animation
			repeatCount += 1;
		}
		else {

			// Move to next column
			currentFrame.x += 1;

			// Check for beyond last column
			if( currentFrame.x >= currentAnimation.rowColumns.x ) {

				// Go to first column
				currentFrame.x = 0;
				// Go to next row
				currentFrame.y += 1;
			}

			// Check for beyond last row
			if( currentFrame.y >= currentAnimation.rowColumns.y ) {

				// Go to first row
				currentFrame.y = 0;
				// Go to first column
				currentFrame.x = 0;
			}
		}
	}

	// Update the source rectangle
	sourceRectangle.x = (int)(currentFrame.x * currentAnimation.frameSize.x);
	sourceRectangle.y = (int)(currentFrame.y * currentAnimation.frameSize.y);
	sourceRectangle.w = (int)( currentAnimation.frameSize.x);
	sourceRectangle.h = (int)( currentAnimation.frameSize.y);
}


