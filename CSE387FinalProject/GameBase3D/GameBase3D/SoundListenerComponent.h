#pragma once
#include "SoundBaseComponent.h"

class SoundListenerComponent : public SoundBaseComponent
{
public:

	SoundListenerComponent( Actor* owner );

	/**
	 * Updates the position, orientation, and up and forward
	 * directions of the listener
	 */
	virtual void Update( float deltaTime ) override;
};

