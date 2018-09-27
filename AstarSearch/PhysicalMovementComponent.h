#pragma once
#include "Component.h"
#include "Actor.h"
class PhysicalMovementComponent :
	public Component
{
public:
	PhysicalMovementComponent(class Actor* owner, int updateOrder = 10);
	~PhysicalMovementComponent();

	void Update(float deltaTime) override;

//	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return glm::length(mVelocity); }
//	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mVelocity = speed * glm::normalize(mVelocity); }
	void SetVelocity(vec2 velocity) { mVelocity = velocity; }

protected:
	vec2 mVelocity;
	vec2 mAcceleration;
};

