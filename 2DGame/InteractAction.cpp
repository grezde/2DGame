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
	if (std::count(positions.begin(), positions.end(), player->lookingAt())) {
		player->setEmote(1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			Game::curent()->setNextScene(false, new SpeechBoxScene(data));
	}
	else
		player->setEmote(0);

}

