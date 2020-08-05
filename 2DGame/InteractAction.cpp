#include "InteractAction.h"
#include "Player.h"
#include <algorithm>
#include "Game.h"
#include "WalkingScene.h"
#include "SpeechBoxScene.h"

void InteractAction::addLocation(int x, int y)
{
	positions.push_back(sf::Vector2i(x, y));
}

void InteractAction::update(float dt)
{
	for(auto pos : positions)
		if (player->lookingAtI() == pos && !room->positionValid(player->lookingAt()))
			player->setEmote(1);
	player->setEmote(0);
}

void InteractAction::trigger()
{
	Game::curent()->setNextScene(false, new SpeechBoxScene(data));
}

void InteractAction::onKeyPress(sf::Keyboard::Key key)
{
	if (key != sf::Keyboard::Z && key != sf::Keyboard::Enter)
		return;

	for (auto pos : positions)
		if (player->lookingAtI() == pos && !room->positionValid(player->lookingAt())) {
			trigger();
			return;
		}
}

