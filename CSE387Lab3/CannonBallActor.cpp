#include "CannonBallActor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "PhysicalMovementComponent.h"

CannonBallActor::CannonBallActor(Game* game) : Actor(game)
{	
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/BulletBill.png"));

	

	PhysicalMovementComponent* mc = new PhysicalMovementComponent(this);

	mc->setVelocity(vec2(0.01, -1));
	mc->SetForwardSpeed(250.0f);
}