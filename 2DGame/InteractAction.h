#pragma once
#include "Action.h"

class InteractAction : public Action
{
private:
	std::vector<sf::Vector2i> positions;
	static float cooldown;
	static bool inProgress;

public:
	static const float TIME_INTERVAL;

public:
	InteractAction(std::vector<std::string> data) : Action(data) {};

	void addLocation(int x, int y);
	void update(float dt);
	void reinitScene();
	void trigger();

};

