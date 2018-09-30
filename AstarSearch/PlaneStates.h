#pragma once
#include "AIState.h"
#include "Plane.h"


class PlaneState : public AIState {
public:
	PlaneState(class AIComponent* owner, class Plane* plane, class Project1Game* game)
		: AIState(owner), planeOwner(plane), gameOwner(game)
	{}

	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual const char* GetName() const = 0;

protected:
	class Plane* planeOwner;
	class Project1Game* gameOwner;

	const float attackRange = 300;
};

class PlanePatrol : public PlaneState
{
public:
	PlanePatrol(class AIComponent* owner, class Plane* plane, class Project1Game* game)
		:PlaneState(owner, plane, game)
	{ }

	// Override with behaviors for this state
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Patrol";
	}
private:
	vec2 orbitCenter;
	float orbitRadius = 50;
};

class PlaneDeath : public PlaneState
{
public:
	PlaneDeath(class AIComponent* owner, class Plane* plane, class Project1Game* game)
		:PlaneState(owner, plane, game)
	{ }

	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Death";
	}
};

class PlaneAttack : public PlaneState
{
public:
	PlaneAttack(class AIComponent* owner, class Plane* plane, class Project1Game* game)
		:PlaneState(owner, plane, game)
	{ }

	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Attack";
	}
};
