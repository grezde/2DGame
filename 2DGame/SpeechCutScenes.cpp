#include "SpeechCutScenes.h"
#include "Globals.h"

void WelcomeSCS::onFinished()
{
	Globals::save->seti("coords_from_save", 1);
	Globals::save->sets("current_room", "johnson_classroom");
	Globals::save->seti("current_player_x", 500);
	Globals::save->seti("current_player_y", 600);
	Globals::save->seti("current_player_rot", 0);
	Globals::save->loadToFile(false);
	next = new WalkingScene("johnson_classroom");
}
