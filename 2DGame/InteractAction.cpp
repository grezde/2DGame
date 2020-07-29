#include "InteractAction.h"
#include "Player.h"
#include <algorithm>
#include "Game.h"
#include "WalkingScene.h"
#include "SpeechBoxScene.h"

const float InteractAction::TIME_INTERVAL = 1.0f;
float InteractAction::cooldown = -1.0f;
bool InteractAction::inProgress = false;

void InteractAction::addLocation(int x, int y)
{
	positions.push_back(sf::Vector2i(x, y));
}

void InteractAction::update(float dt)
{
	for(auto pos : positions)
		if (player->lookingAtI() == pos && !room->positionValid(player->lookingAt())) {
			player->setEmote(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && cooldown < 0 && !inProgress) {
				cooldown = TIME_INTERVAL;
				inProgress = true;
				trigger();
				return;
			}
		}
	player->setEmote(0);
	if(!inProgress && cooldown > 0)
		cooldown -= dt;
}

void InteractAction::reinitScene()
{
	inProgress = false;
}

void InteractAction::trigger()
{
	Game::curent()->setNextScene(false, new SpeechBoxScene(data));
}

