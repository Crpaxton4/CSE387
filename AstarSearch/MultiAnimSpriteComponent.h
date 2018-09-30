#pragma once
#include "SpriteComponent.h"
#include <unordered_map>
#include <vector>

class MultiAnimSpriteComponent : public SpriteComponent
{
public:

	MultiAnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	// Update animation every frame (overriden from component)
	void Update(float deltaTime) override;

	// Set the textures used for animation
	void AddAnimation(const std::string animationName, const std::vector<SDL_Texture*>& textures);

	void PlayAnimation(const std::string animationName);

	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

protected:

	std::unordered_map< std::string, std::vector<SDL_Texture*> > mAnimationMap;

	// All textures in the animation
	std::vector<SDL_Texture*> mCurrentAnimationTextures;

	// Current frame displayed
	float mCurrFrame = 0.0f;

	// Animation frame rate
	float mAnimFPS = 24.0f;
};


