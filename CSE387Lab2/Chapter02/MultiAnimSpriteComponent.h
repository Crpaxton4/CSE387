#pragma once
#include "AnimSpriteComponent.h"
#include "Animation.h"

class MultiAnimSpriteComponent : public AnimSpriteComponent
{
public:
	MultiAnimSpriteComponent(Actor* owner, int numframesPerRow, int numRows, int drawOrder = 100);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetTexture(SDL_Texture* spriteSheet) override;
	void setCurrentAnimation(int index);
	void setAnimations(std::vector<Animation> anims);
	void setDefaultAnim(int index) { defaultAnim = animations[index]; }
	void startIdleState();
	int getAnimIndex() { return animIndex; }


private:
	void getCurrAnimSrcRect(SDL_Rect &rect);

	int framesPerRow;
	int rows;

	int frameHeight;
	int frameWidth;

	// Collection of individual animations in the sprite sheet
	std::vector<Animation> animations;
	Animation defaultAnim;
	Animation currAnim;
	int animIndex;
};

