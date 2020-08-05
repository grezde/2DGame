#include "StartAction.h"
#include "Player.h"
#include "TeleportAction.h"

void StartAction::preinit()
{
	takeAction = true;
}

void StartAction::addLocation(int x, int y)
{
	startx = x;
	starty = y;
}

void StartAction::init()
{
	if(takeAction)
		player->setPosition(sf::Vector2f(startx + 0.5f, starty + 1.0f));
}
