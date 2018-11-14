#include "LightComponent.h"
#include "SharedGeneralLighting.h"
#include "Actor.h"

LightComponent::LightComponent(class Actor* owner, int lightNum, int updateOrder)
:Component(owner, updateOrder) {
	this->lightNum = lightNum;
}

void LightComponent::setEnabled(bool enabled) {
	isEnabled = enabled;
	SharedGeneralLighting::setEnabled((lightSource)lightNum, enabled);
}

void LightComponent::toggle() {
	isEnabled = !isEnabled;
	SharedGeneralLighting::setEnabled((lightSource)lightNum, isEnabled);
}

void LightComponent::setAmbient(vec4 ambient) {
	SharedGeneralLighting::setAmbientColor((lightSource)lightNum, ambient);
}

void LightComponent::setDiffuse(vec4 diffuse) {
	SharedGeneralLighting::setDiffuseColor((lightSource)lightNum, diffuse);
}

void LightComponent::setSpecular(vec4 specular) {
	SharedGeneralLighting::setSpecularColor((lightSource)lightNum, specular);
}

void LightComponent::setDirectional(vec3 direction) {
	isDirectional = true;
	SharedGeneralLighting::setPositionOrDirection((lightSource)lightNum, vec4(direction, 0.0f));
}

void LightComponent::setPositional(vec3 position) {
	isDirectional = false;
	SharedGeneralLighting::setPositionOrDirection((lightSource)lightNum, vec4(position, 1.0f));
}

void LightComponent::makeSpotlight(vec3 direction, vec3 position, float cutOffCos, float falloff) {
	SharedGeneralLighting::setIsSpot((lightSource)lightNum, true);
	SharedGeneralLighting::setPositionOrDirection((lightSource)lightNum, vec4(position, 1.0f));
	SharedGeneralLighting::setSpotDirection((lightSource)lightNum, direction);
	SharedGeneralLighting::setSpotCutoffCos((lightSource)lightNum, cutOffCos);
	SharedGeneralLighting::setSpotExponent((lightSource)lightNum, falloff);
}


// Update this component by delta time
void LightComponent::Update(float deltaTime) {
	if (!isDirectional) {
		SharedGeneralLighting::setPositionOrDirection((lightSource)lightNum, vec4(mOwner->GetPosition(), 1.0f));
	}
}
// Process input for this component
void LightComponent::ProcessInput(const uint8_t* keyState) {
	//TODO
}

// Called when world transform changes
void LightComponent::OnUpdateWorldTransform() {
	//TODO 
}