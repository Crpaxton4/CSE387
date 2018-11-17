#include "Tank.h"
#include "Bullet.h"
#include <ctime>


Tank::Tank(Project1Game* game)
	:Enemy(game),
	bulletCoolDown(0.0f)
{
	srand(time(NULL));
	tankId = (rand() % 3 + 1);

	SSc = new SpriteSheetAnimCompnent(this, true);


	SpriteSheetAnimation anim;
	for (int i = 0; i < 3; i++) {
		anim.startingFrame = vec2(0, i);
		anim.endingFrame = vec2(7, i);
		anim.rowColumns = vec2(8, 3);
		anim.textureName = "Assets/Tanks.png";
		anim.framePerSec = 24.0f;
		anim.loopTimes = -1;

		SSc->AddAnimation("tank" + i, anim, true);
	}

	for (int i = 0; i < 3; i++) {
		anim.startingFrame = vec2(0, i);
		anim.endingFrame = vec2(0, i);
		anim.rowColumns = vec2(8, 3);
		anim.textureName = "Assets/Tanks.png";
		anim.framePerSec = 24.0f;
		anim.loopTimes = -1;

		SSc->AddAnimation("idletank" + i, anim);
	}

	Cc = new CircleComponent(this);
	Cc->SetRadius(30.0f);

	SSc->PlayAnimation("Tank" + tankId); //get a random color for the tank

}


void Tank::UpdateActor(float deltaTime) {
	moveTimer -= deltaTime;
	bulletCoolDown -= deltaTime;
	vec2 newPos = GetPosition();
	vec2 moveVector(0, 0);

	vec2 walkerPos = ((Project1Game*)GetGame())->getWalker()->GetPosition();
	float dist = glm::length(walkerPos - GetPosition());

	if (dist < 300.0f) { //can see walker
		vec2 facing = walkerPos - GetPosition();
		if (facing.x < 0) {
			SSc->SetFlip(SDL_FLIP_HORIZONTAL);
		}

		SetRotation(atan2(-facing.y, facing.x));

		if (bulletCoolDown < 0.0f) {
			Bullet* b = new Bullet((Project1Game*)GetGame(), false);
			b->SetPosition(GetPosition());
			b->SetRotation(GetRotation());
			bulletCoolDown = 3.0f;
		}
	}
	else { //randomy move around

		if (x < 0) {
			SSc->SetFlip(SDL_FLIP_HORIZONTAL);
		}

		if (moveTimer < 0.0f) {
			srand(time(NULL)*(int)deltaTime % 17);
			x = rand();
			srand((int)deltaTime % 13);
			y = rand();


			moveTimer = 7.0f;
		}

		if (moveTimer > 5.0f) {

			moveVector = glm::normalize(vec2(-x, y));
			newPos = GetPosition() + moveVector;
		}
		else {
			moveVector = vec2(0, 0);
			newPos = GetPosition();
		}
	}

	float gHeight = 768.0f;
	float gWidth = 1024.0f;

	float padding = 32.0f;

	if (newPos.x < padding)
	{
		newPos.x = padding;
	}
	else if (newPos.x > gWidth - padding)
	{
		newPos.x = gWidth - padding;
	}
	if (newPos.y < 192.0f)
	{
		newPos.y = 192.0f; //Water line on background
	}
	else if (newPos.y > gHeight - padding)
	{
		newPos.y = gHeight - padding;
	}
	SetPosition(newPos);
	SetRotation(atan2(-moveVector.y, moveVector.x)); // update roation for explosion impact
}

Tank::~Tank()
{
}
