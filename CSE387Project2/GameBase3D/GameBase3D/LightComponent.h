#pragma once
#include "Component.h"
#include "ShapeGame.h"

class LightComponent :
	public Component
{
public:
	LightComponent(class Actor* owner, int updateOrder = 100);

	void setEnabled(bool enabled);

	void setAmbient(vec4 ambient);

	void setDiffuse(vec4 diffuse);

	void setSpecular(vec4 specular);

	void setDirectional(vec3 direction);

	void makeSpotlight(vec3 direction, vec3 position, float spread, float falloff);

	// Update this component by delta time
	void Update(float deltaTime) override;
	// Process input for this component
	void ProcessInput(const uint8_t* keyState) override;
	// Called when world transform changes
	void OnUpdateWorldTransform() override;

private:
	static int lightCount;
	int lightNum;
	bool isSpot = false;
	bool isDirectional = false;
};

int LightComponent::lightCount = 0;