#include "Project1Game.h"
#include "Walker.h"


Project1Game::Project1Game() :Game()
{
}

void Project1Game::LoadData() {
	// Create new Walker on the bottom left corner of the screen
	Walker* walker = new Walker(this);
	walker->SetPosition(vec2(500.0f, 500.0f));
	walker->SetScale(0.75f);
	//Create Barriers in the middle of the area. Not sure of layout currently

	//Create enemy Base in the top right corner (no need to add enemies because base handles that)

	//possibly create background, but may just use solid colors
}

void Project1Game::UnloadData() {

}


Project1Game::~Project1Game()
{
}
