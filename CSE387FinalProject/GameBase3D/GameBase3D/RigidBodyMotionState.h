#pragma once

#include "PhysicsEngine.h"
#include "Actor.h"

class SceneNode;

class RigidBodyMotionState : public btMotionState
{
public:

	RigidBodyMotionState(Actor * node);

	// Called by bullet to get the position and orientation of the object
	virtual void getWorldTransform(btTransform &worldTrans) const;

	// Callled by bullet to set the position and orientation of the object
	virtual void setWorldTransform(const btTransform &worldTrans);

	Actor * sceneNodePtr;
	btTransform bulletTransform;

};

