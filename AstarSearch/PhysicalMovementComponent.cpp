#include "PhysicalMovementComponent.h"



PhysicalMovementComponent::PhysicalMovementComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	mAcceleration = vec2(0, 100);
}


PhysicalMovementComponent::~PhysicalMovementComponent()
{
}

void PhysicalMovementComponent::Update(float deltaTime)
{

		vec2 pos = mOwner->GetPosition();
		mVelocity += mAcceleration * deltaTime;
		pos += mVelocity * deltaTime;

		mOwner->SetRotation(atan2(-mVelocity.y, mVelocity.x));

		// (Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);

}
