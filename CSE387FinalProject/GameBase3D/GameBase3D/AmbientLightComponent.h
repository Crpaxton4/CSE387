#pragma once
#include "LightComponent.h"
class AmbientLightComponent :public LightComponent
{
public:
	AmbientLightComponent(class Actor* owner, lightSource id, bool enabled);
	void ProcessInput(const uint8_t* keyState);
};

