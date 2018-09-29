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

		mOwner->SetPosition(pos);

}
