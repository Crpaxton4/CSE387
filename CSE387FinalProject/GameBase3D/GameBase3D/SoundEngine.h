#pragma once

#include "MathLibsConstsFuncs.h"

// Includes for the FMOD Sound Engine
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

class SoundEngine 
{
public:

	/**
	 * Initialize the sound engine.
	 */
	static bool Init();

	/**
	 * Update the sound engine. Call this once each frame.
	 */
	static void Update(const float & deltaTime = 0.0f);

	/**
	 * Stop the sound engine. Call when closing down
	 */
	static void Stop();

	/**
	 * Call to display errors from sound engine functions.
	*/
	static void HandleError(FMOD_RESULT result);

	/**
	 * The main system object for FMOD Studio.
	 */
	static FMOD::System* system;
};

