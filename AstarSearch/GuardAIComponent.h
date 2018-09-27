#pragma once
#include "AIComponent.h"

class GuardAIComponent : public AIComponent
{
	public:
	GuardAIComponent( class Actor* owner );

	Actor * nearestEnemy = nullptr;

	float maxViewRange = 30;

};

