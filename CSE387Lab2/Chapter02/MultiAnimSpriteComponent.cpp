#include "MultiAnimSpriteComponent.h"
#include "Actor.h"
#include "Game.h"

MultiAnimSpriteComponent::MultiAnimSpriteComponent(Actor* owner, int drawOrder, SDL_Texture* TextureSheet)
	:AnimSpriteComponent(owner, drawOrder)
{
	SpriteComponent::SetTexture(TextureSheet);
}

void MultiAnimSpriteComponent::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		SDL_Rect spriteBoundingRec;
		// Scale the width/height by owner's scale
		spriteBoundingRec.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		spriteBoundingRec.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		spriteBoundingRec.x = static_cast<int>(mOwner->GetPosition().x - spriteBoundingRec.w / 2);
		spriteBoundingRec.y = static_cast<int>(mOwner->GetPosition().y - spriteBoundingRec.h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		// See https://wiki.libsdl.org/SDL_RenderCopyEx
		SDL_RenderCopyEx(renderer,
			mTexture,
			getCurrAnimSrcRect(), // Override because srcRect is now needed as the whole texture is not used
			&spriteBoundingRec,
			-glm::degrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void MultiAnimSpriteComponent::Update(float deltaTime) {

	SpriteComponent::Update(deltaTime);

	if (currAnim.numFrames > 0) {

		// Update the current frame based on frame rate and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		if (mCurrFrame >= currAnim.numFrames) {

			mCurrFrame -= currAnim.numFrames; // = 0;??
		}
	}

}

void MultiAnimSpriteComponent::setAnimations(std::vector<Animation> anims) {
	animations = anims;
	defaultAnim = animations[0];
}


void MultiAnimSpriteComponent::setCurrentAnimation(int index) {

	currAnim = animations[index];
	mCurrFrame = 0.0f;

}

SDL_Rect* MultiAnimSpriteComponent::getCurrAnimSrcRect() {
	SDL_Rect srcRect;

	int framesPerRow = mTexWidth / frameWidth;

	srcRect.x = frameWidth * ((currAnim.startIndex + static_cast<int>(mCurrFrame)) % framesPerRow);
	srcRect.y = std::floor(srcRect.x / framesPerRow);
	srcRect.w = frameWidth;
	srcRect.h = frameHeight;
}


