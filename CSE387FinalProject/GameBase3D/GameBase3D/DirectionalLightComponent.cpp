#include "DirectionalLightComponent.h"
#include "Game.h"
#include "Actor.h"
DirectionalLightComponent::DirectionalLightComponent(class Actor* owner, lightSource id, bool enabled) 
	:LightComponent(owner, id, enabled)
{
	OnUpdateWorldTransform( );
}

void DirectionalLightComponent::OnUpdateWorldTransform()
{
	SharedGeneralLighting::setPositionOrDirection( id, vec4( -mOwner->GetForward( ), 0.0f ) );
}


void DirectionalLightComponent::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_D]) {
		if (enabled) {
			setDisable();
		}
		else {
			setEnable();
		}
	}
}