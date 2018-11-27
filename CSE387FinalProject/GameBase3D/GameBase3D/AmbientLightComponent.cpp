#include "AmbientLightComponent.h"
#include "Game.h"
AmbientLightComponent::AmbientLightComponent(class Actor* owner, lightSource id, bool enabled) 
	:LightComponent(owner, id, enabled)
{
}
void AmbientLightComponent::ProcessInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_A]) {
		if (enabled) {
			setDisable();
		}
		else {
			setEnable();
		}

	}
}