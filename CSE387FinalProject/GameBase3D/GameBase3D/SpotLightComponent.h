#pragma once
#include "LightComponent.h"
class SpotLightComponent :public LightComponent
{
public:
	SpotLightComponent(class Actor* owner, lightSource id, bool enabled);

	void ProcessInput(const uint8_t* keyState) override;

	void OnUpdateWorldTransform() override;

	void setSpotCutoffCos(float cosine);

	void setSpotExponent(float ex);

	
};

