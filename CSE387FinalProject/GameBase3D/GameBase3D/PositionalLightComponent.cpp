#include "PositionalLightComponent.h"
#include "Actor.h"
#include "Game.h"

PositionalLightComponent::PositionalLightComponent(class Actor* owner, lightSource id, bool enabled) 
	:LightComponent(owner,id,enabled)
{
	OnUpdateWorldTransform( );
}


void PositionalLightComponent::OnUpdateWorldTransform()
{
	SharedGeneralLighting::setPositionOrDirection(id, vec4( mOwner->GetPosition( WORLD ), 1.0f ) );

}

void PositionalLightComponent::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_P]) {
		if (enabled) {
			setDisable();
		}
		else {
			setEnable();
		}

	}
}