#include "InteractAction.h"
#include "Player.h"
#include <algorithm>

void InteractAction::addLocation(int x, int y)
{
	positions.push_back(sf::Vector2i(x, y));
}

void InteractAction::update(float dt)
{
	if (std::count(positions.begin(), positions.end(), player->lookingAt()))
		player->setEmote(1);
	else
		player->setEmote(0);
}

