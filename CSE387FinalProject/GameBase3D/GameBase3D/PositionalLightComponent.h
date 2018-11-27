#pragma once
#include "Component.h"
#include "LightComponent.h"
#include "SharedGeneralLighting.h"
class PositionalLightComponent : public LightComponent
{
public:
	PositionalLightComponent(class Actor* owner, lightSource id, bool enabled);

	void OnUpdateWorldTransform() override;

	void ProcessInput(const uint8_t* keyState) override;


};

