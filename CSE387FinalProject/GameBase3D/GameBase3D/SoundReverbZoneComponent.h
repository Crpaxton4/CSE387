#pragma once

#include "SoundBaseComponent.h"

class SoundReverbZoneComponent : 	public SoundBaseComponent
{
public:
	SoundReverbZoneComponent( class Actor* owner, float mindist = 10.0f, float maxdist = 20.0f);

	virtual void Update( float deltaTime ) override;

protected:
	FMOD::Reverb3D *reverb;
	float mindist;
	float maxdist;
};

