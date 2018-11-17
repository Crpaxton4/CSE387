#pragma once
#include "SpriteComponent.h"
#include <unordered_map>
#include "MathLibsConstsFuncs.h"

// Info on one of several possible animations in a sprite sheet
struct SpriteSheetAnimation
{
	vec2 startingFrame; // Zero based row and col of animation starting frame
	vec2 endingFrame;   // Zero based row and col of animation ending frame
	vec2 frameSize;     // Width and height of animation frames in texels
	vec2 rowColumns;    // Number of rows and columns in the sprite sheet.
	vec2 dimensions;	// Resolution of the texture in texels
	int loopTimes = -1; // Number of times to repeat. -1 to loop forever.
	float framePerSec = 24.0f; // Frame to display per second.
	std::string textureName; // path and name of the texture
	SDL_Texture* spriteTexture; // pointer to the loaded texture
};


class SpriteSheetAnimCompnent : public SpriteComponent
{
	public:

	// Constructor
	SpriteSheetAnimCompnent( class Actor* owner, int drawOrder = 100 );

	// Draw method that uses a source rectangle
	virtual void Draw( SDL_Renderer* renderer ) override;

	// Update animation every frame (overriden from component)
	void Update( float deltaTime ) override;

	// Set the textures used for animation
	void AddAnimation( const std::string animationName, SpriteSheetAnimation animation, bool calcFrameSize = true );

	// Plays the animation with the specified name.
	void PlayAnimation( const std::string animationName );

	// Set/get the animation FPS
	void SetFlip( SDL_RendererFlip flip ) { mFlip = flip; }
	SDL_RendererFlip GetFlip( ) const { return mFlip; }

	protected:

	// Map containing the animations represented at Animation
	std::unordered_map< std::string, SpriteSheetAnimation > mAnimationMap;

	// Data about an animation in the sprite sheet
	SpriteSheetAnimation currentAnimation;

	// Row and column of the current frame in the sprite sheet
	vec2 currentFrame;

	// Current source rectange for rendering the sprite
	SDL_Rect sourceRectangle;

	// Set the source rectangle for the next image in the sprite sheet
	void GetNextAnimationFrame( );

	// Total time current frame displayed
	float frameTime = 0.0f;

	// Number of times current frame repeated
	int repeatCount = 0;

	// Animation frame rate
	float mAnimFPS = 2.0f;

	// Sprites can be fliped both horizontally (SDL_FLIP_HORIZONTAL) 
	// and vertically (SDL_FLIP_VERTICAL)
	SDL_RendererFlip mFlip = SDL_FLIP_NONE;
};

