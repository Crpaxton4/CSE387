#include "LightComponent.h"
#include "Actor.h"
#include "Game.h"

LightComponent::LightComponent(class Actor* owner, lightSource id, bool enabled) :Component(owner), id(id)
{
	SharedGeneralLighting::setEnabled(id, enabled);
}


void LightComponent::setEnable()
{
	SharedGeneralLighting::setEnabled(id, true);
}
void LightComponent::setDisable()
{
	SharedGeneralLighting::setEnabled(id, false);
}

void LightComponent::setAmbientColor(vec4 newAmb)
{
	ambientColor = newAmb;
	SharedGeneralLighting::setAmbientColor(id, ambientColor);
}

void LightComponent::setDiffuseColor(vec4 newDif)
{
	diffuseColor = newDif;
	SharedGeneralLighting::setDiffuseColor(id, diffuseColor);
}

void LightComponent::setSpecularColor(vec4 newSpec)
{
	specularColor = newSpec;
	SharedGeneralLighting::setSpecularColor(id, specularColor);
}