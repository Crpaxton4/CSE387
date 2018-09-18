#include "MultiAnimSpriteComponent.h"


MultiAnimSpriteComponent::MultiAnimSpriteComponent( class Actor* owner, int drawOrder)
	:SpriteComponent( owner, drawOrder )
{
}


void MultiAnimSpriteComponent::Update( float deltaTime )
{
	// Call the super class update
	SpriteComponent::Update( deltaTime );

	if( mCurrentAnimationTextures.size( ) > 0 ) {

		// Update the current frame based on frame rate and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		if( mCurrFrame >= mCurrentAnimationTextures.size( ) ) {

			mCurrFrame -= mCurrentAnimationTextures.size( ); 
		}

		// Set the current texture
		SpriteComponent::SetTexture( mCurrentAnimationTextures[static_cast<int>( mCurrFrame )] );
	}
}


void MultiAnimSpriteComponent::AddAnimation( const std::string animationName, const std::vector<SDL_Texture*>& textures/*, const float fps*/ )
{
	mAnimationMap.emplace( animationName, textures);
}


void MultiAnimSpriteComponent::PlayAnimation( const std::string animationName )
{
	// Find the Animation in the map
	auto iter = mAnimationMap.find( animationName );

	// Check if it was found
	if( iter != mAnimationMap.end( ) ) {

		// Set the animation vector containint the animations to be played
		mCurrentAnimationTextures = iter->second;
		// Set the current frame to the first frame
		mCurrFrame = 0.0;
	}
	else {
		SDL_Log( "Could not find %s in animation map", animationName.c_str( ) );

	}
}
