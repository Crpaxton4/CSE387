#include "Plane.h"
#include "PlaneStates.h"


Plane::Plane(Project1Game* game)
	:Enemy(game)
{
	//SetScale(0.4f); //the sprites need to be  40% of their original size
	SSc = new SpriteSheetAnimCompnent(this, false);

	Cc = new CircleComponent(this);
	Cc->SetRadius(24.0f);

	SpriteSheetAnimation circle;
	circle.startingFrame = vec2(0, 0);
	circle.endingFrame = vec2(5, 5);
	circle.frameSize = vec2(64, 64);
	circle.rowColumns = vec2(6, 6);
	circle.textureName = "Assets/Plane.png";
	circle.framePerSec = 20.0f; // want to circle at about 2PI rads per second and 36 framaes akes a full rotation in the sheet
	circle.loopTimes = -1;

	SSc->AddAnimation("circle", circle);

	SpriteSheetAnimation constant;
	constant.startingFrame = vec2(0, 3);
	constant.endingFrame = vec2(0, 3);
	constant.frameSize = vec2(224, 224);
	constant.rowColumns = vec2(6, 6);
	constant.textureName = "Assets/Plane.png";
	constant.framePerSec = 24.0f; // match with the rest of the game sinethere is not reasin not to

	SSc->AddAnimation("constant", constant);


	AIc = new AIComponent(this);
	// Register states with AIComponent
	AIc->RegisterState(new PlanePatrol(AIc, this, (Project1Game*)GetGame()));
	AIc->RegisterState(new PlaneDeath(AIc, this, (Project1Game*)GetGame()));
	AIc->RegisterState(new PlaneAttack(AIc, this, (Project1Game*)GetGame()));

	// Start in patrol state
	SetPosition(vec2(500, 500));
	AIc->ChangeState("Patrol");

}

void Plane::changeAnimation(std::string animation) {
	if (animation == "constant") SSc->useRotation();
	else SSc->noRotation();

	SSc->PlayAnimation(animation);
}

void Plane::Damage(bool missile) {
	if (missile) totalHealth -= 2;
	else totalHealth -= 1;

	if (totalHealth <= 0) {
		AIc->ChangeState("Death");
	}
}

Plane::~Plane()
{
}
