// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <glm/gtx/matrix_decompose.hpp>

Actor::Actor(Game* game)
	:mState(EActive)
	,mPosition(ZERO_V3)
	,mScale(1.0f)
	,mRotation(mat4(1.0))
	,mGame(game)
	,mRecomputeLocalTransform(true)
{
	//mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}

	// Delete all children
	for (Actor * child : children)
	{
		delete child;
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		ComputeLocalTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeLocalTransform();

		// Update all children
		for (Actor * child : children)
		{
			child->Update(deltaTime);
		}
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}

}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);

		// Process input for children
		for (Actor * child : children)
		{
			child->ProcessInput(keyState);
		}
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::SetLocalTransform(glm::mat4 transform)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transform, scale, rotation, translation, skew, perspective);

	mScale = (scale.x + scale.y + scale.z) / 3.0f;
	mPosition = translation;
	mRotation = glm::toMat4(rotation);

	this->mRecomputeLocalTransform = true;
}

void Actor::ComputeLocalTransform()
{
	if (mRecomputeLocalTransform)
	{
		mRecomputeLocalTransform = false;
		
		// Translate, rotate, and scale
		mLocalTransform = 
			glm::translate( mPosition ) *
			mRotation *
			glm::scale( vec3( mScale, mScale, mScale ) );

		// Inform components world transform updated
		for (auto comp : mComponents)
		{
			comp->OnUpdateLocalTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

float Actor::GetScale(Frame frame)
{
	if (frame == Frame::LOCAL)
	{
		// Get the scale in local coordinates
		return mScale;
	} else
	{
		// Get the scale in world coordinates
		float localScale = mScale;
		if (this->parent == nullptr)
		{
			return localScale;
		} else
		{
			return this->parent->GetScale(frame) * localScale;
		}
	}
}

glm::vec3 Actor::GetPosition(Frame frame)
{
	glm::vec3 position;

	// TODO

	return position;
}

glm::mat4 Actor::GetRotation(Frame frame)
{
	// TODO
	return mRotation;
}

void Actor::SetScale(float scale, Frame frame)
{
	mRecomputeLocalTransform = true;
	if (frame == Frame::LOCAL)
	{
		mScale = scale;
	} else
	{
		if (this->parent == nullptr)
		{
			mScale = scale;
		} else
		{
			float parentWorldScale = this->parent->GetScale(Frame::WORLD);
			float parentWorldScaleInverse = 1.0f / parentWorldScale;
			mScale = parentWorldScaleInverse * scale;
		}
	}
}

void Actor::SetPosition(glm::vec3 position, Frame frame)
{
	mRecomputeLocalTransform = true;

	// TODO
	mPosition = position;
}

void Actor::SetRotation(glm::mat4 rotation, Frame frame)
{
	mRecomputeLocalTransform = true;

	// TODO
}

glm::vec3 Actor::GetFacingDirection(Frame frame)
{
	// TODO
	return FORWARD;

}

glm::vec3 Actor::GetUpDirection( Frame frame )
{
	// TODO
	return UP;
}


void Actor::AddChild( Actor *  child )
{
	children.push_back( child );
	child->parent = this;
}



glm::mat4 Actor::GetParentWorldTransform( )
{
	if( parent == nullptr ) {

		return mat4( 1.0f );
	}
	else {
		return parent->GetWorldTransformation( );
	}
}


glm::mat4 Actor::GetLocalTransformation( )
{
	return mLocalTransform;
}


glm::mat4 Actor::GetWorldTransformation( )
{
	return GetParentWorldTransform() * mLocalTransform;
}



void Actor::removeChild( Actor *  child )
{
	auto iter = std::find( children.begin( ), children.end( ), child );
	if( iter != children.end( ) ) {

		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap( iter, children.end( ) - 1 );
		children.pop_back( );
	}

} // end removeChild


void Actor::Reparent( Actor * child )
{

	// TODO

} // end reparent


void Actor::DetachFromParent( )
{
	// TODO

} // end detachFromParent