#include "MultiAnimSpriteComponent.h"
#include "Actor.h"
#include "Game.h"

MultiAnimSpriteComponent::MultiAnimSpriteComponent(Actor* owner, int numFramesPerRow, int numRows, int drawOrder)
	:AnimSpriteComponent(owner, drawOrder)
{
	framesPerRow = numFramesPerRow;
	rows = numRows;
}

void MultiAnimSpriteComponent::Draw(SDL_Renderer* renderer) {
	if (SpriteComponent::getTexture()) {

		SDL_Rect spriteBoundingRec;
		// Scale the width/height by owner's scale
		spriteBoundingRec.w = static_cast<int>(frameWidth * mOwner->GetScale());
		spriteBoundingRec.h = static_cast<int>(frameHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		spriteBoundingRec.x = static_cast<int>(mOwner->GetPosition().x - spriteBoundingRec.w / 2);
		spriteBoundingRec.y = static_cast<int>(mOwner->GetPosition().y - spriteBoundingRec.h / 2);


		SDL_Rect rect;
		getCurrAnimSrcRect(rect);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		// See https://wiki.libsdl.org/SDL_RenderCopyEx
		SDL_RenderCopyEx(renderer,
			SpriteComponent::getTexture(),
			&rect, // srcRect is now needed as the whole texture is not used
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

void MultiAnimSpriteComponent::SetTexture(SDL_Texture* spriteSheet) {
	SpriteComponent::SetTexture(spriteSheet);

	frameWidth = SpriteComponent::GetTexWidth() / framesPerRow;
	frameHeight = SpriteComponent::GetTexHeight() / rows;

}

void MultiAnimSpriteComponent::setAnimations(std::vector<Animation> anims) {
	animations = anims;
	defaultAnim = animations[0];
}


void MultiAnimSpriteComponent::setCurrentAnimation(int index) {
	if (index != animIndex) {
		animIndex = index;
		currAnim = animations[index];
		mCurrFrame = 0.0f;
	}

}

void MultiAnimSpriteComponent::getCurrAnimSrcRect(SDL_Rect &rect) {

	rect.x = frameWidth * ((currAnim.startIndex + static_cast<int>(mCurrFrame)) % framesPerRow);
	rect.y = frameHeight * ((currAnim.startIndex + static_cast<int>(mCurrFrame)) / framesPerRow);
	rect.w = frameWidth;
	rect.h = frameHeight;

	std::cout << "X: " << rect.x <<
	std::endl << "Y: " << rect.y <<
	std::endl << "W: " << rect.w <<
	std::endl << "H: " << rect.h << std::endl;

	std::cout << static_cast<int>(mCurrFrame) << std::endl;
}

void MultiAnimSpriteComponent::startIdleState() {
	currAnim = defaultAnim;
}


