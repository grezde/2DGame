#include "TeleportAction.h"
#include "Player.h"
#include "Game.h"
#include "WalkingScene.h"

const float TeleportAction::TIME_INTERVAL = 0.2f;
const sf::Vector2f TeleportAction::OFFSET_ON_TELEPORT = sf::Vector2f(0.5f, 0.8f);
std::string TeleportAction::lastTeleport = "";

TeleportAction::TeleportAction(std::vector<std::string> data)
	: Action(data)
{
	nextRoom = data[0];
	if (data[1][1] == 'x')
		dloc.x = 1;
	else
		dloc.y = 1;
	if (data[1][0] == '-')
		dloc *= -1;
}

TeleportAction::~TeleportAction()
{
}

void TeleportAction::init()
{
	if (lastTeleport.empty())
		return;

	if (lastTeleport == nextRoom) {
		//StartAction::stopActing();
		player->setPosition(sf::Vector2f(locations.back().x, locations.back().y) + OFFSET_ON_TELEPORT);
	}
}

void TeleportAction::addLocation(int x, int y)
{
	locations.push_back(sf::Vector2i(x, y));
}

void TeleportAction::update(float dt)
{
	for (auto loc : locations)
		if (loc.x == int(player->position().x) && loc.y == int(player->position().y)) {
			if (player->lookingAtI() == loc + dloc && player->walking()) {
				countdown += dt;
				if (countdown >= TIME_INTERVAL) {
					lastTeleport = room->name();
					Game::curent()->setNextScene(true, new WalkingScene(nextRoom));
				}
				return;
			}
		}
	countdown = 0;
}
