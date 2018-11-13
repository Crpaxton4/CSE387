#include "ReparentComponent.h"



ReparentComponent::ReparentComponent(Actor* owner, Actor* otherParent)
	:Component(owner), otherParent(otherParent)
{
}

void ReparentComponent::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_P] && timeSinceLastReparent > 1.0f)
	{
		Actor* lastParent = this->mOwner->GetParent();
		if (lastParent != nullptr && otherParent != nullptr)
		{
			std::cout << "Actor is being reparented" << std::endl;
			Actor* lastParent = this->mOwner->GetParent();
			otherParent->Reparent(this->mOwner);
			otherParent = lastParent;
		}
		timeSinceLastReparent = 0.0f;
	}
}

void ReparentComponent::Update(float deltaTime)
{
	timeSinceLastReparent += deltaTime;
}

