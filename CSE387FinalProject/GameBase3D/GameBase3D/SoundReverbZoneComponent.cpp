#include "SoundReverbZoneComponent.h"

#include "Actor.h"



SoundReverbZoneComponent::SoundReverbZoneComponent( class Actor* owner, float mindist, float maxdist)
	:SoundBaseComponent( owner ),mindist( mindist ), maxdist( maxdist )
{
	FMOD_RESULT result = SoundEngine::system->createReverb3D(&reverb);

	if (result == FMOD_OK)
	{
		FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
		SoundEngine::HandleError(reverb->setProperties(&prop2));

		FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
		SoundEngine::HandleError(reverb->set3DAttributes(&pos, mindist, maxdist));
	}
	else {
		SoundEngine::HandleError(result);
	}
}


void SoundReverbZoneComponent::Update( float deltaTime )
{
	// Calculate the World position and orientation 
	SoundBaseComponent::Update(deltaTime);

	SoundEngine::HandleError(reverb->set3DAttributes(&fmod_pos, mindist, maxdist));
}
