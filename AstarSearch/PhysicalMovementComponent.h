#pragma once
#include "Component.h"
#include "Actor.h"
class PhysicalMovementComponent :
	public Component
{
public:
	PhysicalMovementComponent(class Actor* owner, float m, float frict, float initialVelocity = 0.0f, int updateOrder = 10);

	void Update(float deltaTime) override;
	void addForce(vec2 force);

	vec2 getVelocity() { return mVelocity; }
	vec2 getAcceleration() { return mAcceleration; }

protected:
	vec2 mVelocity;
	vec2 mAcceleration;
	float mass;
	float frictionCoef;
	const float Grav = 9.8f;
};

