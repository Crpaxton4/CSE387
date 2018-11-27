#pragma once
#include "LightComponent.h"
class DirectionalLightComponent :public LightComponent
{
public:
	DirectionalLightComponent(class Actor* owner, lightSource id, bool enabled);

	void OnUpdateWorldTransform( ) override;

	void ProcessInput(const uint8_t* keyState) override;

};

