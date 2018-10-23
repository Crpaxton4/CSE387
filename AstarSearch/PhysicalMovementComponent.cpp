#include "PhysicalMovementComponent.h"



PhysicalMovementComponent::PhysicalMovementComponent(class Actor* owner,float m, float frict,float initialVelocity, int updateOrder)
	:Component(owner, updateOrder),
	mass(m),
	frictionCoef(frict)
{
	mVelocity = glm::normalize(mOwner->GetForward())*initialVelocity;
}

void PhysicalMovementComponent::Update(float deltaTime)
{

		vec2 pos = mOwner->GetPosition();
		mVelocity += mAcceleration * deltaTime;
		mVelocity -= frictionCoef * Grav * mVelocity * deltaTime;
		pos += mVelocity * deltaTime;

		mAcceleration -= frictionCoef * mAcceleration;

		mOwner->SetRotation(atan2(-mVelocity.y, mVelocity.x));

		mOwner->SetPosition(pos);

}

void PhysicalMovementComponent::addForce(vec2 force) {
	mAcceleration += force / mass;
}
