#pragma once
#include "AnimSpriteComponent.h"
#include "Animation.h"

class MultiAnimSpriteComponent : public AnimSpriteComponent
{
public:
	MultiAnimSpriteComponent(Actor* owner, int drawOrder, SDL_Texture* TextureSheet);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void setCurrentAnimation(int index);
	void setAnimations(std::vector<Animation> anims);
	void setDefaultAnim(int index){defaultAnim = animations[index];};


private:
	SDL_Rect* getCurrAnimSrcRect();
	int frameHeight;
	int frameWidth;

	// Collection of individual animations in the sprite sheet
	std::vector<Animation> animations;
	Animation defaultAnim;
	Animation currAnim;
};

