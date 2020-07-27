#pragma once
#include "Action.h"

class TeleportAction : public Action
{
private:
	sf::Vector2i dloc;
	std::vector<sf::Vector2i> locations;
	std::string nextRoom;

	static std::string lastTeleport;
	static bool teleported;

	float countdown = 0;
	static const float TIME_INTERVAL;
	static const sf::Vector2f OFFSET_ON_TELEPORT;

public:
	TeleportAction(std::vector<std::string> data);

	static bool teleportedThisScene() { return teleported; }

public:

	void preinit();
	void init();
	void addLocation(int x, int y);
	void update(float dt);
};

