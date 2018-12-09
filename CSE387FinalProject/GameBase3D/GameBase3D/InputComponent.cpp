// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"
#include "SDL/SDL_scancode.h"
#include <iostream>
InputComponent::InputComponent(class Actor* owner)
:MoveComponent(owner)
,mForwardKey(0)
,mBackKey(0)
,mClockwiseKey(0)
,mCounterClockwiseKey(0)
{
	
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float xRotation = 0.0f;
	float yRotation = 0.0f;

	if (keyState[SDL_SCANCODE_UP]) {
		xRotation += 0.5f;
		std::cout << "Up" << std::endl;
	}

	if (keyState[SDL_SCANCODE_DOWN]) {
		xRotation -= 0.5f;
		std::cout << "Down" << std::endl;
	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		yRotation += 0.5f;
		std::cout << "Left" << std::endl;
	}

	if (keyState[SDL_SCANCODE_RIGHT]) {
		yRotation -= 0.5f;
		std::cout << "Right" << std::endl;
	}


	setXRotation(xRotation);
	setYRotation(yRotation);

	vec3 pos = mOwner->GetPosition();

	vec3 forward = mOwner->GetForward();

	vec3 lat = glm::normalize(glm::cross(forward, vec3(0, 1, 0)));

	if (keyState[SDL_SCANCODE_W]) {
		pos += 0.5f * forward;
	}

	if (keyState[SDL_SCANCODE_S]) {
		pos -= 0.5f * forward;
	}

	if (keyState[SDL_SCANCODE_A]) {
		pos -= 0.5f * lat;
	}

	if (keyState[SDL_SCANCODE_D]) {
		pos += 0.5f * lat;
	}

	mOwner->SetPosition(pos, LOCAL);
}
