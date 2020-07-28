#include "InteractAction.h"
#include "Player.h"
#include <algorithm>
#include "Game.h"
#include "WalkingScene.h"
#include "SpeechBoxScene.h"

const float InteractAction::TIME_INTERVAL = 0.5f;

void InteractAction::addLocation(int x, int y)
{
	positions.push_back(sf::Vector2i(x, y));
}

void InteractAction::update(float dt)
{
	for(auto pos : positions)
		if (player->lookingAtI() == pos && !room->positionValid(player->lookingAt())) {
			player->setEmote(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && cooldown < 0) {
				cooldown = TIME_INTERVAL;
				Game::curent()->setNextScene(false, new SpeechBoxScene(data));
				return;
			}
		}
	player->setEmote(0);

	if (cooldown > 0)
		cooldown -= dt;
}

