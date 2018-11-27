#include "RigidBodyMotionState.h"

#include "MathLibsConstsFuncs.h"



RigidBodyMotionState::RigidBodyMotionState(Actor * node)
{
	sceneNodePtr = node;
}



// Called by bullet to get the position and orientation of the object
void RigidBodyMotionState::getWorldTransform(btTransform &worldTrans) const
{
	// Calculate current world transformation and set world trans to it 
	worldTrans = PhysicsEngine::convertTransform( sceneNodePtr->GetWorldTransformation( ) );//   getWorldTransformation( ));
}

// Callled by bullet to set the position and orient the object
void RigidBodyMotionState::setWorldTransform(const btTransform &worldTrans)
{
	// silently return before we set a node
	if (sceneNodePtr != nullptr) {

		bulletTransform = worldTrans;

		glm::mat4 T = PhysicsEngine::convertTransform(worldTrans);

		sceneNodePtr->SetLocalTransform( glm::inverse( sceneNodePtr->GetParentWorldTransform()) * T);

		//sceneNodePtr->localTransformation = glm::inverse(sceneNodePtr->parent->getWorldTransformation()) * T;
	}
}


